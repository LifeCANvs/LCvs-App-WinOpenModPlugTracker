/* Copyright (C) Teemu Suutari */

#ifndef ILZRDECOMPRESSOR_HPP
#define ILZRDECOMPRESSOR_HPP

#include "XPKDecompressor.hpp"

namespace ancient::internal
{

class ILZRDecompressor : public XPKDecompressor
{
public:
	ILZRDecompressor(uint32_t hdr,uint32_t recursionLevel,const Buffer &packedData,std::shared_ptr<XPKDecompressor::State> &state,bool verify);
	~ILZRDecompressor() noexcept=default;

	const std::string &getSubName() const noexcept final;

	void decompressImpl(Buffer &rawData,const Buffer &previousData,bool verify) final;

	static bool detectHeaderXPK(uint32_t hdr) noexcept;
	static std::shared_ptr<XPKDecompressor> create(uint32_t hdr,uint32_t recursionLevel,const Buffer &packedData,std::shared_ptr<XPKDecompressor::State> &state,bool verify);

private:
	const Buffer	&_packedData;

	size_t		_rawSize{0};
};

}

#endif
