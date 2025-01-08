#include "Other.h"

int Random(int A, int B)
{
	return rand() % (B - A + 1) + A;
}
void HpSleep(int ms)
{
	static clock_t oldclock = clock();		// ��̬��������¼��һ�� tick

	oldclock += ms * CLOCKS_PER_SEC / 1000;	// ���� tick

	if (clock() > oldclock)					// ����Ѿ���ʱ��������ʱ
		oldclock = clock();
	else
		while (clock() < oldclock)			// ��ʱ
			Sleep(1);						// �ͷ� CPU ����Ȩ������ CPU ռ����
}
void ClipboardString(std::string str)
{
	//�����ַ��ͱ������������û����������
	//CString str; 
	HGLOBAL hClip;
	//����һ��HGLOBAL�����������ָ�������ڴ��
	if (OpenClipboard(NULL))
	{
		EmptyClipboard(); //���������������
		hClip = GlobalAlloc(GMEM_MOVEABLE, str.length() + 1);
		//�ڶ��Ϸ�����ƶ����ڴ�飬���򷵻�һ���ڴ���
		char* buff; //����ָ���ַ��͵�ָ�����
		buff = (char*)GlobalLock(hClip);
		//�Է�����ڴ����м��������ڴ����ת����һ��ָ��,������Ӧ�����ü�������1
		strcpy(buff, str.c_str());
		//���û���������ݸ��Ƶ�ָ������У�ʵ���Ͼ��Ǹ��Ƶ�������ڴ����
		GlobalUnlock(hClip);
		//����д����ϣ����н����������������ü��������ּ�1
		SetClipboardData(CF_TEXT, hClip);
		//����������ݵ��ڴ�������������Դ������
		CloseClipboard();
		//�رռ����壬�ͷż�������Դ��ռ��Ȩ
		//MessageBox("�ѽ����ݴ��������");
	}

}
std::string GetClipboardString()
{
	std::string str;
	//�ַ��ͱ��������ɼ����帴������������
	HANDLE hClip;
	//����HANDLE����ͱ�������ָ��GetClipboardData�������صľ��
	if (OpenClipboard(NULL))
	{
		hClip = GetClipboardData(CF_TEXT);
		//�Ӽ�������ȡ��һ���ڴ�ľ��
		char* buff;
		//�����ַ���ָ��������������ڴ���е�����
		buff = (char*)GlobalLock(hClip);
		//���ڴ����м��������ڴ���ֵת��Ϊһ��ָ��,�����ڴ������ü�������һ���ڴ��е�����Ҳ���ص�ָ���ͱ�����
		str = buff;
		//�����ݱ��浽�ַ��ͱ�����
		GlobalUnlock(hClip);
		//���ڴ������ü�������һ
		CloseClipboard();
		//�رռ����壬�ͷż�������Դ��ռ��Ȩ

	}
	return str;
}

//https://blog.csdn.net/c914620529/article/details/73503708
//ANSI��Ӧchar,UTF-8��Ӧchar����,Unicode(UTF-16)��Ӧwchar_t
//ANSI�ַ�����Ӣ��ʹ��һ���ֽڣ�����ʹ�������ֽ�
//Unicode�ַ�����Ӣ�������Ķ�ʹ�������ֽ�
//UTF8�ַ�����Ӣ��ʹ��һ���ֽڣ�����ʹ�������ֽ�

//ANSI-->Unicode
std::wstring StringToWString(const std::string& str)
{
	int num = MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);
	wchar_t* wide = new wchar_t[num];
	MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, wide, num);
	std::wstring wstr = wide;
	delete[] wide;
	return wstr;
}
//Unicode-->ANSI
std::string WStringToString(const std::wstring& wszString)
{
	int num = WideCharToMultiByte(CP_ACP, 0, wszString.c_str(), -1, NULL, 0, NULL, NULL);
	char* wide = new char[num];
	WideCharToMultiByte(CP_ACP, 0, wszString.c_str(), -1, wide, num, NULL, NULL);
	std::string str = wide;
	delete[] wide;
	return str;
}
//UTF8-->Unicode
std::wstring u8StringTouWString(const std::string& str)
{
	int num = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, NULL, 0);
	wchar_t* wide = new wchar_t[num];
	MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, wide, num);
	std::wstring uwstr = wide;
	delete[] wide;
	return uwstr;
}
//Unicode-->UTF8
std::string uWStringTou8String(const std::wstring& wszString)
{
	int num = WideCharToMultiByte(CP_UTF8, 0, wszString.c_str(), -1, NULL, 0, NULL, NULL);
	char* wide = new char[num];
	WideCharToMultiByte(CP_UTF8, 0, wszString.c_str(), -1, wide, num, NULL, NULL);
	std::string str = wide;
	delete[] wide;
	return str;
}
//via @Dewei
//�޸�UrlEncode����
std::string urlencode(std::string& str_source)
{
	char const* in_str = str_source.c_str();
	int in_str_len = (int)strlen(in_str);
	int out_str_len = 0;
	std::string out_str;
	register unsigned char c;
	unsigned char* to, * start;
	unsigned char const* from, * end;
	unsigned char hexchars[] = "0123456789ABCDEF";

	from = (unsigned char*)in_str;
	end = (unsigned char*)in_str + strlen(in_str);
	start = to = (unsigned char*)malloc(3 * strlen(in_str) + 1);

	while (from < end) {
		c = *from++;
		if ((c < '0' && c != '-' && c != '.' && c != '/' && c != '%') ||
			(c < 'A' && c > '9' && c != ':') ||
			(c > 'Z' && c < 'a' && c != '_') ||
			(c > 'z')) {
			to[0] = '%';
			to[1] = hexchars[c >> 4];
			to[2] = hexchars[c & 15];
			to += 3;
		}
		else {
			*to++ = c;
		}
	}
	*to = 0;

	out_str_len = (int)(to - start);
	out_str = (char*)start;
	free(start);
	return out_str;
}
//via @Dewei
static int php_htoi(char* s)
{
	int value;
	int c;

	c = ((unsigned char*)s)[0];
	if (isupper(c))
		c = tolower(c);
	value = (c >= '0' && c <= '9' ? c - '0' : c - 'a' + 10) * 16;

	c = ((unsigned char*)s)[1];
	if (isupper(c))
		c = tolower(c);
	value += c >= '0' && c <= '9' ? c - '0' : c - 'a' + 10;

	return (value);
}
//via @Dewei
//�޸�UrlDecode����
std::string urldecode(std::string& str_source)
{
	char const* in_str = str_source.c_str();
	int in_str_len = (int)strlen(in_str);
	int out_str_len = 0;
	std::string out_str;
	char* str;

	str = _strdup(in_str);
	char* dest = str;
	char* data = str;

	while (in_str_len--) {
		if (*data == '%' && in_str_len >= 2 && isxdigit((int)*(data + 1))
			&& isxdigit((int)*(data + 2))) {
			*dest = (char)php_htoi(data + 1);
			data += 2;
			in_str_len -= 2;
		}
		else {
			*dest = *data;
		}
		data++;
		dest++;
	}
	*dest = '\0';
	out_str_len = (int)(dest - str);
	out_str = str;
	free(str);
	return out_str;
}
std::string GetFileName(std::string& str_path)
{
	unsigned long long pos = str_path.find_last_of("/");
	std::string filename = str_path.substr(pos + 1);
	return filename;
}
int DownloadFromHttp(std::string Url, std::string FileName)
{
	std::wstring wUrl = StringToWString(Url);
	LPCWSTR pwszUrlwstr = wUrl.c_str();

	URL_COMPONENTS urlComp = { 0 };
	DWORD dwUrlLen = 0;
	// ��ʼ�� URL_COMPONENTS �ṹ��.
	ZeroMemory(&urlComp, sizeof(urlComp));
	urlComp.dwStructSize = sizeof(urlComp);
	//����ռ�洢�����������ȡ����Ϣ��ʽ����ȷ
	wchar_t* pScheme = new wchar_t[MAX_PATH]();
	wchar_t* pHostName = new wchar_t[MAX_PATH]();
	wchar_t* pUserName = new wchar_t[MAX_PATH]();
	wchar_t* pPassword = new wchar_t[MAX_PATH]();
	wchar_t* pUrlPath = new wchar_t[MAX_PATH]();
	wchar_t* pExtraInfo = new wchar_t[MAX_PATH]();

	urlComp.lpszScheme = pScheme;
	urlComp.lpszHostName = pHostName;
	urlComp.lpszUserName = pUserName;
	urlComp.lpszPassword = pPassword;
	urlComp.lpszUrlPath = pUrlPath;
	urlComp.lpszExtraInfo = pExtraInfo;

	// ���ñ�Ҫ���������Ϊ���㣬�������ǾͿ��Ա�����.(�ṹ�����ȸ�ֵ)
	urlComp.dwSchemeLength =
		urlComp.dwHostNameLength =
		urlComp.dwUserNameLength =
		urlComp.dwPasswordLength =
		urlComp.dwUrlPathLength =
		urlComp.dwExtraInfoLength = (DWORD)-1;

	//����
	//if (!WinHttpCrackUrl(pwszUrlwstr, (DWORD)wcslen(pwszUrlwstr), 0, &urlComp))
	if (!WinHttpCrackUrl(pwszUrlwstr, 0, 0, &urlComp))
		printf("Error %u in WinHttpCrackUrl.\n", GetLastError());
	else
	{
		std::wstring wUrlPath = pUrlPath;
		std::string u8strUrl = uWStringTou8String(wUrlPath);
		std::string strUrlen = urlencode(u8strUrl); //UrlEncode���ΪӢ���ַ���ANSI��UTF-8�޲��
		std::wstring wstrUrlen = StringToWString(strUrlen);
		//ͬ������ʹ��u8StringTouWString() ת��ΪUnicode
		urlComp.lpszUrlPath = (LPWSTR)wstrUrlen.c_str();
		std::string strUrlde = urldecode(strUrlen);
		std::wstring u8UrlPath = u8StringTouWString(strUrlde);
		std::string strUrlPath = WStringToString(u8UrlPath);

		if (FileName.empty() == 1)
			FileName = GetFileName(strUrlPath);

		LPCSTR lpFileNamestr = FileName.c_str();

		DWORD dwSize = 0;
		DWORD dwSumSize = 0;
		DWORD dwDownloaded = 0;
		DWORD dwBuffer = 0,
		      dwBufferLength = sizeof(DWORD),
			  dwIndex = 0;

		LPSTR pszOutBuffer;
		BOOL  bResults = FALSE;
		HINTERNET  hSession = NULL,
				   hConnect = NULL,
				   hRequest = NULL;

		HANDLE hFile;

		hFile = CreateFileA(lpFileNamestr,  // creates a new file
			FILE_APPEND_DATA,         // open for writing
			FILE_SHARE_READ,          // allow multiple readers
			NULL,                     // no security
			CREATE_ALWAYS,            // creates a new file, always.
			FILE_ATTRIBUTE_NORMAL,    // normal file
			NULL);                    // no attr. template

		if (hFile == INVALID_HANDLE_VALUE)
		{
			printf("Could not creates %s.\n", lpFileNamestr);
			return 2;
		}

		// Use WinHttpOpen to obtain a session handle.
		hSession = WinHttpOpen(L"WinHTTP_Download Example/1.0",
			WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,
			WINHTTP_NO_PROXY_NAME,
			WINHTTP_NO_PROXY_BYPASS, 0);

		// Specify an HTTP server.
		//INTERNET_PORT nPort = (pGetRequest->fUseSSL) ? INTERNET_DEFAULT_HTTPS_PORT : INTERNET_DEFAULT_HTTP_PORT;

		if (hSession)
			hConnect = WinHttpConnect(hSession, urlComp.lpszHostName,
				//hConnect = WinHttpConnect(hSession, L"avatar.csdn.net",
				INTERNET_DEFAULT_HTTPS_PORT, 0);

		// Create an HTTP request handle.
		if (hConnect)
			hRequest = WinHttpOpenRequest(hConnect, L"GET", urlComp.lpszUrlPath,
				L"HTTP/1.1", WINHTTP_NO_REFERER,
				WINHTTP_DEFAULT_ACCEPT_TYPES,
				WINHTTP_FLAG_SECURE);

		// Send a request.
		if (hRequest)
			bResults = WinHttpSendRequest(hRequest,
				WINHTTP_NO_ADDITIONAL_HEADERS,
				0, WINHTTP_NO_REQUEST_DATA, 0,
				0, 0);

		// End the request.
		if (bResults)
			bResults = WinHttpReceiveResponse(hRequest, NULL);

		WinHttpQueryHeaders(hRequest, WINHTTP_QUERY_CONTENT_LENGTH | WINHTTP_QUERY_FLAG_NUMBER, NULL, &dwBuffer, &dwBufferLength, &dwIndex);

		// Continue to verify data until there is nothing left.
		if (bResults)
			do
			{
				// Verify available data.
				dwSize = 0;
				if (!WinHttpQueryDataAvailable(hRequest, &dwSize))
					printf("Error %u in WinHttpQueryDataAvailable.\n",
						GetLastError());

				// Allocate space for the buffer.
				pszOutBuffer = new char[dwSize + (size_t)1];
				if (!pszOutBuffer)
				{
					printf("Out of memory\n");
					dwSize = 0;
				}
				else
				{
					dwSumSize += dwSize;
					printf("Download: %0.2f%%\t%d\t%d\r", dwSumSize * 100.0 / dwBuffer, dwSumSize, dwBuffer); //���������صİٷֱ�
					// Read the Data.
					ZeroMemory(pszOutBuffer, dwSize + (size_t)1);

					if (!WinHttpReadData(hRequest, (LPVOID)pszOutBuffer,
						dwSize, &dwDownloaded)) {
						printf("Error %u in WinHttpReadData.\n", GetLastError());
					}
					else {
						WriteFile(hFile, pszOutBuffer, dwDownloaded, &dwDownloaded, NULL);
					}
					// Free the memory allocated to the buffer.
					delete[] pszOutBuffer;
				}

			} while (dwSize > 0);

			// Close files.
			CloseHandle(hFile);

			// Report any errors.
			if (!bResults)
				printf("Error %d has occurred.\n", GetLastError());

			// Close open handles.
			if (hRequest) WinHttpCloseHandle(hRequest);
			if (hConnect) WinHttpCloseHandle(hConnect);
			if (hSession) WinHttpCloseHandle(hSession);

			delete[]pScheme;
			delete[]pHostName;
			delete[]pUserName;
			delete[]pPassword;
			delete[]pUrlPath;
			delete[]pExtraInfo;
	}
	return 0;
}
int DownloadFromHttp(std::string Url, std::string FileName, void (*Function)(double))
{
	std::wstring wUrl = StringToWString(Url);
	LPCWSTR pwszUrlwstr = wUrl.c_str();

	URL_COMPONENTS urlComp = { 0 };
	DWORD dwUrlLen = 0;
	// ��ʼ�� URL_COMPONENTS �ṹ��.
	ZeroMemory(&urlComp, sizeof(urlComp));
	urlComp.dwStructSize = sizeof(urlComp);
	//����ռ�洢�����������ȡ����Ϣ��ʽ����ȷ
	wchar_t* pScheme = new wchar_t[MAX_PATH]();
	wchar_t* pHostName = new wchar_t[MAX_PATH]();
	wchar_t* pUserName = new wchar_t[MAX_PATH]();
	wchar_t* pPassword = new wchar_t[MAX_PATH]();
	wchar_t* pUrlPath = new wchar_t[MAX_PATH]();
	wchar_t* pExtraInfo = new wchar_t[MAX_PATH]();

	urlComp.lpszScheme = pScheme;
	urlComp.lpszHostName = pHostName;
	urlComp.lpszUserName = pUserName;
	urlComp.lpszPassword = pPassword;
	urlComp.lpszUrlPath = pUrlPath;
	urlComp.lpszExtraInfo = pExtraInfo;

	// ���ñ�Ҫ���������Ϊ���㣬�������ǾͿ��Ա�����.(�ṹ�����ȸ�ֵ)
	urlComp.dwSchemeLength =
		urlComp.dwHostNameLength =
		urlComp.dwUserNameLength =
		urlComp.dwPasswordLength =
		urlComp.dwUrlPathLength =
		urlComp.dwExtraInfoLength = (DWORD)-1;

	//����
	//if (!WinHttpCrackUrl(pwszUrlwstr, (DWORD)wcslen(pwszUrlwstr), 0, &urlComp))
	if (!WinHttpCrackUrl(pwszUrlwstr, 0, 0, &urlComp))
		printf("Error %u in WinHttpCrackUrl.\n", GetLastError());
	else
	{
		std::wstring wUrlPath = pUrlPath;
		std::string u8strUrl = uWStringTou8String(wUrlPath);
		std::string strUrlen = urlencode(u8strUrl); //UrlEncode���ΪӢ���ַ���ANSI��UTF-8�޲��
		std::wstring wstrUrlen = StringToWString(strUrlen);
		//ͬ������ʹ��u8StringTouWString() ת��ΪUnicode
		urlComp.lpszUrlPath = (LPWSTR)wstrUrlen.c_str();
		std::string strUrlde = urldecode(strUrlen);
		std::wstring u8UrlPath = u8StringTouWString(strUrlde);
		std::string strUrlPath = WStringToString(u8UrlPath);

		if (FileName.empty() == 1)
			FileName = GetFileName(strUrlPath);

		LPCSTR lpFileNamestr = FileName.c_str();

		DWORD dwSize = 0;
		DWORD dwSumSize = 0;
		DWORD dwDownloaded = 0;
		DWORD dwBuffer = 0,
			dwBufferLength = sizeof(DWORD),
			dwIndex = 0;

		LPSTR pszOutBuffer;
		BOOL  bResults = FALSE;
		HINTERNET  hSession = NULL,
			hConnect = NULL,
			hRequest = NULL;

		HANDLE hFile;

		hFile = CreateFileA(lpFileNamestr,  // creates a new file
			FILE_APPEND_DATA,         // open for writing
			FILE_SHARE_READ,          // allow multiple readers
			NULL,                     // no security
			CREATE_ALWAYS,            // creates a new file, always.
			FILE_ATTRIBUTE_NORMAL,    // normal file
			NULL);                    // no attr. template

		if (hFile == INVALID_HANDLE_VALUE)
		{
			printf("Could not creates %s.\n", lpFileNamestr);
			return 2;
		}

		// Use WinHttpOpen to obtain a session handle.
		hSession = WinHttpOpen(L"WinHTTP_Download Example/1.0",
			WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,
			WINHTTP_NO_PROXY_NAME,
			WINHTTP_NO_PROXY_BYPASS, 0);

		// Specify an HTTP server.
		//INTERNET_PORT nPort = (pGetRequest->fUseSSL) ? INTERNET_DEFAULT_HTTPS_PORT : INTERNET_DEFAULT_HTTP_PORT;

		if (hSession)
			hConnect = WinHttpConnect(hSession, urlComp.lpszHostName,
				//hConnect = WinHttpConnect(hSession, L"avatar.csdn.net",
				INTERNET_DEFAULT_HTTPS_PORT, 0);

		// Create an HTTP request handle.
		if (hConnect)
			hRequest = WinHttpOpenRequest(hConnect, L"GET", urlComp.lpszUrlPath,
				L"HTTP/1.1", WINHTTP_NO_REFERER,
				WINHTTP_DEFAULT_ACCEPT_TYPES,
				WINHTTP_FLAG_SECURE);

		// Send a request.
		if (hRequest)
			bResults = WinHttpSendRequest(hRequest,
				WINHTTP_NO_ADDITIONAL_HEADERS,
				0, WINHTTP_NO_REQUEST_DATA, 0,
				0, 0);

		// End the request.
		if (bResults)
			bResults = WinHttpReceiveResponse(hRequest, NULL);

		WinHttpQueryHeaders(hRequest, WINHTTP_QUERY_CONTENT_LENGTH | WINHTTP_QUERY_FLAG_NUMBER, NULL, &dwBuffer, &dwBufferLength, &dwIndex);

		// Continue to verify data until there is nothing left.
		if (bResults)
			do
			{
				// Verify available data.
				dwSize = 0;
				if (!WinHttpQueryDataAvailable(hRequest, &dwSize))
					printf("Error %u in WinHttpQueryDataAvailable.\n",
						GetLastError());

				// Allocate space for the buffer.
				pszOutBuffer = new char[dwSize + (size_t)1];
				if (!pszOutBuffer)
				{
					printf("Out of memory\n");
					dwSize = 0;
				}
				else
				{
					dwSumSize += dwSize;
					printf("Download: %0.2f%%\t%d\t%d\r", dwSumSize * 100.0 / dwBuffer, dwSumSize, dwBuffer); //���������صİٷֱ�
					Function(dwSumSize * 100.0 / dwBuffer); //�����ȴ�����Ӧ����
					// Read the Data.
					ZeroMemory(pszOutBuffer, dwSize + (size_t)1);

					if (!WinHttpReadData(hRequest, (LPVOID)pszOutBuffer,
						dwSize, &dwDownloaded)) {
						printf("Error %u in WinHttpReadData.\n", GetLastError());
					}
					else {
						WriteFile(hFile, pszOutBuffer, dwDownloaded, &dwDownloaded, NULL);
					}
					// Free the memory allocated to the buffer.
					delete[] pszOutBuffer;
				}

			} while (dwSize > 0);

			// Close files.
			CloseHandle(hFile);

			// Report any errors.
			if (!bResults)
				printf("Error %d has occurred.\n", GetLastError());

			// Close open handles.
			if (hRequest) WinHttpCloseHandle(hRequest);
			if (hConnect) WinHttpCloseHandle(hConnect);
			if (hSession) WinHttpCloseHandle(hSession);

			delete[]pScheme;
			delete[]pHostName;
			delete[]pUserName;
			delete[]pPassword;
			delete[]pUrlPath;
			delete[]pExtraInfo;
	}
	return 0;
}

//Audio
Audio::~Audio()
{
	std::wstring Command = _T("stop ") + AudioPath;
	mciSendString(Command.c_str(), NULL, NULL, NULL);
	Command = _T("close ") + AudioPath;
	mciSendString(Command.c_str(), NULL, NULL, NULL);
}
Audio::Audio(std::wstring Path)
{
	AudioPath = _T("\"") + Path + _T("\"");
	std::wstring Command = _T("open ") + Path;
	mciSendString(Command.c_str(), NULL, NULL, NULL);
}
void Audio::SetAudioPath(std::wstring Path)
{
	AudioPath = _T("\"") + Path + _T("\"");
	std::wstring Command = _T("open ") + Path;
	mciSendString(Command.c_str(), NULL, NULL, NULL);
}
void Audio::Play()
{
	std::wstring Command = _T("play ") + AudioPath;
	mciSendString(Command.c_str(), NULL, NULL, NULL);
}
void Audio::PlayRepeat()
{
	std::wstring Command = _T("play ") + AudioPath + _T(" repeat");
	mciSendString(Command.c_str(), NULL, NULL, NULL);
}
void Audio::PlayWait()
{
	std::wstring Command = _T("play ") + AudioPath + _T(" wait");
	mciSendString(Command.c_str(), NULL, NULL, NULL);
}
void Audio::Stop()
{
	std::wstring Command = _T("stop ") + AudioPath;
	mciSendString(Command.c_str(), NULL, NULL, NULL);
}
void Audio::Pause()
{
	std::wstring Command = _T("pause ") + AudioPath;
	mciSendString(Command.c_str(), NULL, NULL, NULL);
}
void Audio::Resume()
{
	std::wstring Command = _T("resume ") + AudioPath;
	mciSendString(Command.c_str(), NULL, NULL, NULL);
}
void Audio::Close()
{
	std::wstring Command = _T("stop ") + AudioPath;
	mciSendString(Command.c_str(), NULL, NULL, NULL);
	Command = _T("close ") + AudioPath;
	mciSendString(Command.c_str(), NULL, NULL, NULL);
}
void Audio::Seek(std::wstring S)
{
	std::wstring Command = _T("seek ") + AudioPath + _T(" to ") + S;
	mciSendString(Command.c_str(), NULL, NULL, NULL);
}
void Audio::SetVolume(std::wstring Volume)
{
	std::wstring Command = _T("setaudio ") + AudioPath + _T(" volume to ") + Volume;
	mciSendString(Command.c_str(), NULL, NULL, NULL);
}
double Audio::GetProgress()
{
	TCHAR Ch[100];
	double Num;
	std::wstring Command = _T("status ") + AudioPath + _T(" length");
	mciSendString(Command.c_str(), Ch, 100, NULL);
	Command = Ch;
	Num = _wtof(Command.c_str());
	Command = _T("status ") + AudioPath + _T(" position");
	mciSendString(Command.c_str(), Ch, 100, NULL);
	Command = Ch;
	return _wtof(Command.c_str()) / Num;
}
std::wstring GetFilePath(std::wstring FileType, std::wstring Title)
{
	OPENFILENAME ofn;
	char szFile[300];

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = GetHWnd();
	ofn.lpstrFile = (LPWSTR)szFile;
	ofn.lpstrFile[0] = '\0';
	LPTSTR        lpstrCustomFilter;
	DWORD         nMaxCustFilter;
	ofn.nFilterIndex = 1;
	LPTSTR        lpstrFile;
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = FileType.c_str();
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.lpstrTitle = Title.c_str();

	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_CREATEPROMPT;

	if (GetOpenFileName(&ofn))
		return ofn.lpstrFile;
	else
		return _T("Open Error");
}
std::wstring GetSavePath(std::wstring FileType, std::wstring Title)
{
	OPENFILENAME ofn;
	char szFile[300];

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = GetHWnd();
	ofn.lpstrFile = (LPWSTR)szFile;
	ofn.lpstrFile[0] = '\0';
	LPTSTR        lpstrCustomFilter;
	DWORD         nMaxCustFilter;
	ofn.nFilterIndex = 1;
	LPTSTR        lpstrFile;
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = FileType.c_str();
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.lpstrTitle = Title.c_str();

	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_CREATEPROMPT | OFN_OVERWRITEPROMPT;

	if (GetSaveFileName(&ofn))
		return ofn.lpstrFile;
	else
		return _T("Open Error");
}
