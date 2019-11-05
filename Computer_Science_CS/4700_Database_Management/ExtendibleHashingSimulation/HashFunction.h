#pragma once

// A bitwise hash function written by Justin Sobel
// Code adapted from https://urldefense.proofpoint.com/v2/url?u=http-3A__www.partow.net_programming_hashfunctions_-23RSHashFunction&d=DwIGAg&c=3buyMx9JlH1z22L_G5pM28wz_Ru6WjhVHwo-vpeS0Gk&r=cqARsoQS3FvRkcVh2tPwyd3_tAwqELs9_YxtM0adVHQ&m=FyJVITd8PIwVnLvW2djv6GgpESBRlAI2xffU02NSRJg&s=aMz8OQWyvfxdyTfozVioVrF_XfosdFK1JlO1JVM_oXk&e=

unsigned int hash(const int key)
{
	const char* kptr = (char*)&key;
	unsigned int length = sizeof(int);
	unsigned int hash = 1315423911;
	unsigned int i = 0;

	for (i = 0; i < length; ++kptr, ++i)
	{
		hash ^= ((hash << 5) + (*kptr) + (hash >> 2));
	}

	return hash;
}