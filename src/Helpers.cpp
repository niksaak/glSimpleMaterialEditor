#include <Precompiled.h>

#include "Helpers.h"

//----------------------------------------------------------------------------
const String LoadFileContent(const String& fileName)
{
	String content;
	InputFileStream ifs(fileName);

	if (ifs)
	{
		content = String((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
		ifs.close();
	}
	else
		LOG_ERROR("Can't open file for reading \""<< fileName<< "\".");

	return content;
}
