//------------------------------------------------------------
// ��Ȩ��������֤�Ƽ��ɷ����޹�˾  ��Ȩ����
// �ļ����ƣ�xsdk_libraryop.h
// ģ�����ƣ����ӿ����API
// ģ�������������ӿ�dll/so�ļ��ļ��ء�ж��
// �������ߣ����ı�
// �������ڣ�2012-02-22
// ģ��汾��1.0.000.000
//------------------------------------------------------------
// �޸�����      �汾              ����            ��ע
//------------------------------------------------------------
// 2012-02-22  1.0.000.000         ���ı�          ԭ��
//------------------------------------------------------------

#if !defined(__MA_LIBRARYOP_H__)
#define __MA_LIBRARYOP_H__

#include <xsdk_define.h>

#if defined(OS_IS_WINDOWS)
  #include <windows.h>
#endif  // defined(OS_IS_WINDOWS)

#if defined(OS_IS_LINUX) || defined(OS_IS_AIX)
  #include <unistd.h>
  #include <dlfcn.h>
#endif  // defined(OS_IS_LINUX) || defined(OS_IS_AIX)

#if defined(OS_IS_LINUX) || defined(OS_IS_AIX)
  typedef void * HMODULE;
#endif  // defined(OS_IS_LINUX) || defined(OS_IS_AIX)


class CLibraryOp
{
public:
  HMODULE m_Hmod;

  CLibraryOp()
  {
    HMODULE hMod = NULL;
    m_Hmod = hMod;
  }

  CLibraryOp(const char * p_pszFileName) : m_Hmod(NULL)
  {
    Load(p_pszFileName);
  }

  ~CLibraryOp()
  {
    Free();
  }

  //--------------------------------------------------------------------------------------
  // �������ƣ�Load
  // �������������ڴ�ָ������(p_pszFileName)�Ķ�̬���ӿ⣬�����ز������
  // ����˵����(��)
  // ���˵����[in]   const char*    p_pszFileName    ��    ��̬���ӿ��ļ���
  // ���ؽ����bool  ���ý��
  //                 false    ��ʾ���ؾ��ʧ��
  //                 true     ��ʾ���ؾ���ɹ�
  //--------------------------------------------------------------------------------------
  bool Load(const char* p_pszFileName)
  {
    bool bRetVal = false;
    if (!p_pszFileName)
    {
      goto __end;
    }
    Free();

#if defined OS_IS_WINDOWS
    m_Hmod = ::LoadLibrary(p_pszFileName);
#else
    m_Hmod = dlopen(p_pszFileName, RTLD_NOW);
#endif

    bRetVal = (m_Hmod != NULL);

__end:
    return bRetVal;
  }

  //--------------------------------------------------------------------------------------
  // �������ƣ�Free
  // �������������ڹر�ָ������Ķ�̬���ӿ�
  // ����˵����(��)
  // ���˵����(��)
  // ���ؽ����(��)
  //--------------------------------------------------------------------------------------
  void Free()
  {
    if( IsLoaded() )
    {
#if defined OS_IS_WINDOWS
      ::FreeLibrary(m_Hmod);
#else
      dlclose(m_Hmod);
#endif
      m_Hmod = NULL;
    }
    return ;
  }

  //--------------------------------------------------------------------------------------
  // �������ƣ�IsLoaded
  // ��������������ȷ������Ƿ�ΪNULL
  // ����˵����(��)
  // ���˵����(��)
  // ���ؽ����bool  ���ý��
  //                 false    ��ʾ���ΪNULL
  //                 true     ��ʾ�����ΪNULL
  //--------------------------------------------------------------------------------------
  bool IsLoaded() const
  {
    return m_Hmod != NULL;
  }

  //--------------------------------------------------------------------------------------
  // �������ƣ�GetFuncAddress
  // �����������ж��Ƿ�ȡ������ִ�е�ַ, �������ַ
  // ����˵����(��)
  // ���˵����[in]   const char*    p_pszFileName    ��    ������
  //                  void **       p_pvdAddress     ��    ������ַ
  // ���ؽ����bool  ���ý��
  //                 false    ��ʾ��ȡ��ַʧ��
  //                 true     ��ʾ��ȡ��ַ�ɹ�
  //--------------------------------------------------------------------------------------
  bool GetFuncAddress(void ** p_pvdAddress, const char * p_pszFuncName) const
  {
    bool bRetVal = false;
    if(p_pszFuncName == NULL || !IsLoaded())
    {
      goto __end;
    }

#if defined OS_IS_WINDOWS
    *p_pvdAddress = (void *)::GetProcAddress(m_Hmod, p_pszFuncName);
#endif

#if defined(OS_IS_LINUX) || defined(OS_IS_AIX)
    *p_pvdAddress = dlsym(m_Hmod, p_pszFuncName);
#endif

    bRetVal = (*p_pvdAddress != NULL);

__end:
    return bRetVal;
  }

};

#endif