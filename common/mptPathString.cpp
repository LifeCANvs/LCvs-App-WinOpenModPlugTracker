/*
 * mptPathString.cpp
 * -----------------
 * Purpose: Wrapper class around the platform-native representation of path names. Should be the only type that is used to store path names.
 * Notes  : Currently none.
 * Authors: OpenMPT Devs
 * The OpenMPT source code is released under the BSD license. Read LICENSE for more details.
 */

#include "stdafx.h"
#include "mptPathString.h"

#include <vector>

#if MPT_OS_WINDOWS
#include <windows.h>
#include <tchar.h>
#endif

OPENMPT_NAMESPACE_BEGIN



namespace mpt
{



mpt::RawPathString SupportLongPath(const mpt::RawPathString &path)
{
#if MPT_OS_WINDOWS
#if MPT_OS_WINDOWS_WINRT && (_WIN32_WINNT < 0x0a00)
	// For WinRT on Windows 8, there is no official wy to determine an absolute path.
	return path;
#else // !MPT_OS_WINDOWS_WINRT
	using namespace path_literals;
	using char_type = RawPathString::value_type;
	if(path.length() < MAX_PATH || path.substr(0, 4) == L<char_type>("\\\\?\\"))
	{
		// Path is short enough or already in prefixed form
		return path;
	}
	const RawPathString absPath = mpt::GetAbsolutePath(mpt::PathString::FromNative(path)).AsNative();
	if(absPath.substr(0, 2) == L<char_type>("\\\\"))
	{
		// Path is a network share: \\server\foo.bar -> \\?\UNC\server\foo.bar
		return L<char_type>("\\\\?\\UNC") + absPath.substr(1);
	} else
	{
		// Regular file: C:\foo.bar -> \\?\C:\foo.bar
		return L<char_type>("\\\\?\\") + absPath;
	}
#endif // MPT_OS_WINDOWS_WINRT
#else // !MPT_OS_WINDOWS
	return path;
#endif // MPT_OS_WINDOWS
}



#if MPT_OS_WINDOWS

#if !MPT_OS_WINDOWS_WINRT

int PathCompareNoCase(const PathString & a, const PathString & b)
{
	return lstrcmpi(a.AsNative().c_str(), b.AsNative().c_str());
}

#endif // !MPT_OS_WINDOWS_WINRT

#endif // MPT_OS_WINDOWS



bool NativePathTraits::IsPathSeparator(RawPathString::value_type c)
{
	using namespace path_literals;
	using char_type = RawPathString::value_type;
#if MPT_OS_WINDOWS || MPT_OS_DJGPP
	return (c == L<char_type>('\\')) || (c == L<char_type>('/'));
#else
	return c == L<char_type>('/');
#endif
}



RawPathString::value_type NativePathTraits::GetDefaultPathSeparator()
{
	using namespace path_literals;
	using char_type = RawPathString::value_type;
#if MPT_OS_WINDOWS || MPT_OS_DJGPP
	return L<char_type>('\\');
#else
	return L<char_type>('/');
#endif
}



// Convert a path to its simplified form, i.e. remove ".\" and "..\" entries
// Note: We use our own implementation as PathCanonicalize is limited to MAX_PATH
// and unlimited versions are only available on Windows 8 and later.
// Furthermore, we also convert forward-slashes to backslashes and always remove trailing slashes.
RawPathString NativePathTraits::Simplify(const RawPathString &path)
{

	using namespace path_literals;
	using char_type = RawPathString::value_type;

	if(path.empty())
	{
		return RawPathString();
	}

#if MPT_OS_WINDOWS

	std::vector<RawPathString> components;
	RawPathString root;
	RawPathString::size_type startPos = 0;
	if(path.size() >= 2 && path[1] == L<char_type>(':'))
	{
		// Drive letter
		root = path.substr(0, 2) + L<char_type>('\\');
		startPos = 2;
	} else if(path.substr(0, 2) == L<char_type>("\\\\"))
	{
		// Network share
		root = L<char_type>("\\\\");
		startPos = 2;
	} else if(path.substr(0, 2) == L<char_type>(".\\") || path.substr(0, 2) == L<char_type>("./"))
	{
		// Special case for relative paths
		root = L<char_type>(".\\");
		startPos = 2;
	} else if(path.size() >= 1 && (path[0] == L<char_type>('\\') || path[0] == L<char_type>('/')))
	{
		// Special case for relative paths
		root = L<char_type>("\\");
		startPos = 1;
	}

	while(startPos < path.size())
	{
		auto pos = path.find_first_of(L<char_type>("\\/"), startPos);
		if(pos == RawPathString::npos)
		{
			pos = path.size();
		}
		RawPathString dir = path.substr(startPos, pos - startPos);
		if(dir == L<char_type>(".."))
		{
			// Go back one directory
			if(!components.empty())
			{
				components.pop_back();
			}
		} else if(dir == L<char_type>("."))
		{
			// nop
		} else if(!dir.empty())
		{
			components.push_back(std::move(dir));
		}
		startPos = pos + 1;
	}

	RawPathString result = root;
	result.reserve(path.size());
	for(const auto &component : components)
	{
		result += component + L<char_type>("\\");
	}
	if(!components.empty())
	{
		result.pop_back();
	}

#else // !MPT_OS_WINDOWS
	
	std::vector<RawPathString> components;
	RawPathString root;
	RawPathString::size_type startPos = 0;
	if(path.substr(0, 2) == L<char_type>("./"))
	{
		// Special case for relative paths
		root = L<char_type>("./");
		startPos = 2;
	} else if(path.size() >= 1 && (path[0] == L<char_type>('/')))
	{
		// Special case for relative paths
		root = L<char_type>("/");
		startPos = 1;
	}

	while(startPos < path.size())
	{
		auto pos = path.find_first_of(L<char_type>("/"), startPos);
		if(pos == RawPathString::npos)
		{
			pos = path.size();
		}
		RawPathString dir = path.substr(startPos, pos - startPos);
		if(dir == L<char_type>(".."))
		{
			// Go back one directory
			if(!components.empty())
			{
				components.pop_back();
			}
		} else if(dir == L<char_type>("."))
		{
			// nop
		} else if(!dir.empty())
		{
			components.push_back(std::move(dir));
		}
		startPos = pos + 1;
	}

	RawPathString result = root;
	result.reserve(path.size());
	for(const auto &component : components)
	{
		result += component + L<char_type>("/");
	}
	if(!components.empty())
	{
		result.pop_back();
	}

#endif // MPT_OS_WINDOWS

	return result;

}



void NativePathTraits::SplitPath(RawPathString p, RawPathString *prefix, RawPathString *drive, RawPathString *dir, RawPathString *fbase, RawPathString *fext)
{

	using namespace path_literals;
	using char_type = RawPathString::value_type;

	if(prefix) *prefix = RawPathString();
	if(drive) *drive = RawPathString();
	if(dir) *dir = RawPathString();
	if(fbase) *fbase = RawPathString();
	if(fext) *fext = RawPathString();

#if MPT_OS_WINDOWS

	// We cannot use CRT splitpath here, because:
	//  * limited to _MAX_PATH or similar
	//  * no support for UNC paths
	//  * no support for \\?\ prefixed paths

	// remove \\?\\ prefix
	if(p.substr(0, 8) == L<char_type>("\\\\?\\UNC\\"))
	{
		if(prefix) *prefix = L<char_type>("\\\\?\\UNC");
		p = L<char_type>("\\\\") + p.substr(8);
	} else if(p.substr(0, 4) == L<char_type>("\\\\?\\"))
	{
		if (prefix) *prefix = L<char_type>("\\\\?\\");
		p = p.substr(4);
	}

	if(p.length() >= 2 && (
		p.substr(0, 2) == L<char_type>("\\\\")
		|| p.substr(0, 2) == L<char_type>("\\/")
		|| p.substr(0, 2) == L<char_type>("/\\")
		|| p.substr(0, 2) == L<char_type>("//")
		))
	{ // UNC
		RawPathString::size_type first_slash = p.substr(2).find_first_of(L<char_type>("\\/"));
		if(first_slash != RawPathString::npos)
		{
			RawPathString::size_type second_slash = p.substr(2 + first_slash + 1).find_first_of(L<char_type>("\\/"));
			if(second_slash != RawPathString::npos)
			{
				if(drive) *drive = p.substr(0, 2 + first_slash + 1 + second_slash);
				p = p.substr(2 + first_slash + 1 + second_slash);
			} else
			{
				if(drive) *drive = p;
				p = RawPathString();
			}
		} else
		{
			if(drive) *drive = p;
			p = RawPathString();
		}
	} else
	{ // local
		if(p.length() >= 2 && (p[1] == L<char_type>(':')))
		{
			if(drive) *drive = p.substr(0, 2);
			p = p.substr(2);
		} else
		{
			if(drive) *drive = RawPathString();
		}
	}
	RawPathString::size_type last_slash = p.find_last_of(L<char_type>("\\/"));
	if(last_slash != RawPathString::npos)
	{
		if(dir) *dir = p.substr(0, last_slash + 1);
		p = p.substr(last_slash + 1);
	} else
	{
		if(dir) *dir = RawPathString();
	}
	RawPathString::size_type last_dot = p.find_last_of(L<char_type>("."));
	if(last_dot == RawPathString::npos)
	{
		if(fbase) *fbase = p;
		if(fext) *fext = RawPathString();
	} else if(last_dot == 0)
	{
		if(fbase) *fbase = p;
		if(fext) *fext = RawPathString();
	} else if(p == L<char_type>(".") || p == L<char_type>(".."))
	{
		if(fbase) *fbase = p;
		if(fext) *fext = RawPathString();
	} else
	{
		if(fbase) *fbase = p.substr(0, last_dot);
		if(fext) *fext = p.substr(last_dot);
	}

#else // !MOT_OS_WINDOWS

	RawPathString::size_type last_slash = p.find_last_of(L<char_type>("/"));
	if(last_slash != RawPathString::npos)
	{
		if(dir) *dir = p.substr(0, last_slash + 1);
		p = p.substr(last_slash + 1);
	} else
	{
		if(dir) *dir = RawPathString();
	}
	RawPathString::size_type last_dot = p.find_last_of(L<char_type>("."));
	if(last_dot == RawPathString::npos)
	{
		if(fbase) *fbase = p;
		if(fext) *fext = RawPathString();
	} else if(last_dot == 0)
	{
		if(fbase) *fbase = p;
		if(fext) *fext = RawPathString();
	} else if(p == L<char_type>(".") || p == L<char_type>(".."))
	{
		if(fbase) *fbase = p;
		if(fext) *fext = RawPathString();
	} else
	{
		if(fbase) *fbase = p.substr(0, last_dot);
		if(fext) *fext = p.substr(last_dot);
	}

#endif // MPT_OS_WINDOWS

}



#if defined(MODPLUG_TRACKER) && MPT_OS_WINDOWS


// Convert an absolute path to a path that's relative to "&relativeTo".
mpt::PathString AbsolutePathToRelative(const mpt::PathString &path, const mpt::PathString &relativeTo)
{
	using namespace path_literals;
	using char_type = RawPathString::value_type;
	mpt::PathString result = path;
	if(path.empty())
	{
		return result;
	}
	if(!_tcsncicmp(relativeTo.AsNative().c_str(), path.AsNative().c_str(), relativeTo.AsNative().length()))
	{
		// Path is OpenMPT's directory or a sub directory ("C:\OpenMPT\Somepath" => ".\Somepath")
		result = mpt::PathString::FromNative(L<char_type>(".\\")); // ".\"
		result += mpt::PathString::FromNative(path.AsNative().substr(relativeTo.AsNative().length()));
	} else if(!_tcsncicmp(relativeTo.AsNative().c_str(), path.AsNative().c_str(), 2))
	{
		// Path is on the same drive as OpenMPT ("C:\Somepath" => "\Somepath")
		result = mpt::PathString::FromNative(path.AsNative().substr(2));
	}
	return result;
}


// Convert a path that is relative to "&relativeTo" to an absolute path.
mpt::PathString RelativePathToAbsolute(const mpt::PathString &path, const mpt::PathString &relativeTo)
{
	using namespace path_literals;
	using char_type = RawPathString::value_type;
	mpt::PathString result = path;
	if(path.empty())
	{
		return result;
	}
	if(path.length() >= 2 && path.AsNative()[0] == L<char_type>('\\') && path.AsNative()[1] == L<char_type>('\\'))
	{
		// Network / UNC paths
		return result;
	} if(path.length() >= 1 && path.AsNative()[0] == L<char_type>('\\'))
	{
		// Path is on the same drive as relativeTo ("\Somepath\" => "C:\Somepath\")
		result = mpt::PathString::FromNative(relativeTo.AsNative().substr(0, 2));
		result += mpt::PathString(path);
	} else if(path.length() >= 2 && path.AsNative().substr(0, 2) == L<char_type>(".\\"))
	{
		// Path is in relativeTo or a sub directory (".\Somepath\" => "C:\OpenMPT\Somepath\")
		result = relativeTo; // "C:\OpenMPT\"
		result += mpt::PathString::FromNative(path.AsNative().substr(2));
	} else if(path.length() < 3 || path.AsNative()[1] != L<char_type>(':') || path.AsNative()[2] != L<char_type>('\\'))
	{
		// Any other path not starting with drive letter
		result = relativeTo;  // "C:\OpenMPT\"
		result += mpt::PathString(path);
	}
	return result;
}


#endif // MODPLUG_TRACKER && MPT_OS_WINDOWS



bool NativePathTraits::IsAbsolute(const RawPathString &path)
{
#if MPT_OS_WINDOWS
	using namespace path_literals;
	using char_type = RawPathString::value_type;
	if(path.substr(0, 8) == L<char_type>("\\\\?\\UNC\\"))
	{
		return true;
	}
	if(path.substr(0, 4) == L<char_type>("\\\\?\\"))
	{
		return true;
	}
	if(path.substr(0, 2) == L<char_type>("\\\\"))
	{
		return true; // UNC
	}
	if(path.substr(0, 2) == L<char_type>("//"))
	{
		return true; // UNC
	}
	return (path.length()) >= 3 && (path[1] == L<char_type>(':')) && IsPathSeparator(path[2]);
#else
	return (path.length() >= 1) && IsPathSeparator(path[0]);
#endif
}



#if MPT_OS_WINDOWS

#if !(MPT_OS_WINDOWS_WINRT && (_WIN32_WINNT < 0x0a00))

mpt::PathString GetAbsolutePath(const mpt::PathString &path)
{
	DWORD size = GetFullPathName(path.AsNative().c_str(), 0, nullptr, nullptr);
	if(size == 0)
	{
		return path;
	}
	std::vector<TCHAR> fullPathName(size, TEXT('\0'));
	if(GetFullPathName(path.AsNative().c_str(), size, fullPathName.data(), nullptr) == 0)
	{
		return path;
	}
	return mpt::PathString::FromNative(fullPathName.data());
}

#endif

#endif // MPT_OS_WINDOWS



} // namespace mpt



#if defined(MODPLUG_TRACKER)



static inline char SanitizePathComponentChar(char c)
{
	if(	c == '\\' ||
		c == '\"' ||
		c == '/'  ||
		c == ':'  ||
		c == '?'  ||
		c == '<'  ||
		c == '>'  ||
		c == '|'  ||
		c == '*')
	{
		c = '_';
	}
	return c;
}

static inline wchar_t SanitizePathComponentChar(wchar_t c)
{
	if(	c == L'\\' ||
		c == L'\"' ||
		c == L'/'  ||
		c == L':'  ||
		c == L'?'  ||
		c == L'<'  ||
		c == L'>'  ||
		c == L'|'  ||
		c == L'*')
	{
		c = L'_';
	}
	return c;
}

#if MPT_CXX_AT_LEAST(20)
static inline char8_t SanitizePathComponentChar(char8_t c)
{
	if(	c == u8'\\' ||
		c == u8'\"' ||
		c == u8'/'  ||
		c == u8':'  ||
		c == u8'?'  ||
		c == u8'<'  ||
		c == u8'>'  ||
		c == u8'|'  ||
		c == u8'*')
	{
		c = u8'_';
	}
	return c;
}
#endif

mpt::PathString SanitizePathComponent(const mpt::PathString &filename)
{
	mpt::RawPathString tmp = filename.AsNative();
	for(auto &c : tmp)
	{
		c = SanitizePathComponentChar(c);
	}
	return mpt::PathString::FromNative(tmp);
}

std::string SanitizePathComponent(std::string str)
{
	for(size_t i = 0; i < str.length(); i++)
	{
		str[i] = SanitizePathComponentChar(str[i]);
	}
	return str;
}

std::wstring SanitizePathComponent(std::wstring str)
{
	for(size_t i = 0; i < str.length(); i++)
	{
		str[i] = SanitizePathComponentChar(str[i]);
	}
	return str;
}

#if MPT_USTRING_MODE_UTF8
mpt::u8string SanitizePathComponent(mpt::u8string str)
{
	for(size_t i = 0; i < str.length(); i++)
	{
		str[i] = SanitizePathComponentChar(str[i]);
	}
	return str;
}
#endif // MPT_USTRING_MODE_UTF8

#if defined(MPT_WITH_MFC)
CString SanitizePathComponent(CString str)
{
	for(int i = 0; i < str.GetLength(); i++)
	{
		str.SetAt(i, SanitizePathComponentChar(str.GetAt(i)));
	}
	return str;
}
#endif // MPT_WITH_MFC



#endif // MODPLUG_TRACKER



OPENMPT_NAMESPACE_END
