#ifndef DXGIINFOMANAGER_H_INCLUDED
#define DXGIINFOMANAGER_H_INCLUDED

#include "win.h"
#include <wrl.h>
#include <vector>
#include <dxgidebug.h>
#include <string>

class DxgiInfoManager
{
public:
	DxgiInfoManager();
	~DxgiInfoManager() = default;;

	DxgiInfoManager(const DxgiInfoManager & other) = delete;
	DxgiInfoManager(DxgiInfoManager && other) = delete;
	DxgiInfoManager& operator=(const DxgiInfoManager & other) = delete;
	DxgiInfoManager& operator=(DxgiInfoManager && other) = delete;

	void Set() noexcept;
	std::vector<std::string> GetMessages() const;

private:
	unsigned long long next = 0u;
	Microsoft::WRL::ComPtr<IDXGIInfoQueue> pDxgiInfoQueue;

};


#endif // !DXGIINFOMANAGER_H_INCLUDED
