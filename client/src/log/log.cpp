#include "log.h"

namespace nario {
	void log::err(LPCTSTR pstrFormat, ...)
	{
		CTime timeWrite;
		timeWrite = CTime::GetCurrentTime();
		CString str = timeWrite.Format(_T("%d %b %y %H:%M:%S - ")); // todo:time
		ATLTRACE(str);

		va_list args;
		va_start(args, pstrFormat);
		str.FormatV(pstrFormat, args);
		ATLTRACE(str);
		std::cout << str << std::endl;
	}

	void log::info(LPCTSTR pstrFormat, ...)
	{
		CString str = "";
		va_list args;
		va_start(args, pstrFormat);
		str.FormatV(pstrFormat, args);
		ATLTRACE(str);
		std::cout << str << std::endl;
		return;
	}

}
