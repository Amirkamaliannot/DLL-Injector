#include <iostream>
#include <Windows.h>

DWORD GetProcId(const char* procName) {

	HWND acWindow = FindWindow(nullptr, procName);
	
	DWORD procID;
	GetWindowThreadProcessId(acWindow, &procID);

	return procID;

}


int main() {
	const char* dllpath = "C:\\game\\Dark Souls III The Ringed City\\Game\\binkw64.dll";
	const char* procName = "AssaultCube";

	DWORD procID = GetProcId(procName);

	HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, NULL, procID);

	if (hProc) {
		std::cout << "Process attached"<<std::endl;

		void* spaseForDLLpath = VirtualAllocEx(hProc, nullptr, strlen(dllpath), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

		if (spaseForDLLpath) {

			std::cout << "memory allocate at : " << spaseForDLLpath << std::endl;

			WriteProcessMemory(hProc, spaseForDLLpath, dllpath, strlen(dllpath), nullptr );

			HANDLE hThread = CreateRemoteThread(hProc, NULL, NULL, (LPTHREAD_START_ROUTINE)LoadLibraryA, spaseForDLLpath, NULL, nullptr );

			if (hThread) {
				CloseHandle(hThread);
			}
			else {
				std::cout << "Thread not created !!!";
			}
		}
		else {

			std::cout << "Memory not alocate !!!" << std::endl;
		}
		CloseHandle(hProc);
	}
	else {

		std::cout << "Process not attached !!!" << std::endl;
	}


}