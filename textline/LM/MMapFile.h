/******************************************************************************
 *
 * File     :MMapFile.h
 * Version  :$Id: MMapFile.h,v 1.9 2005/09/19 09:23:39 kwq Exp $
 * Desc     :Ӳ���ļ�Ӱ���ļ��༰һЩ��Ӳ���ļ�Ӱ���һЩ����
 * Log		:Created by victor, 2004-12-24
 *
 ******************************************************************************/
#ifndef MMAPFILE_H
#define MMAPFILE_H

//#include "AFX.h"
#include <iostream>
#include <assert.h>
#ifdef _WIN32
#	include <windows.h>
#else
#	include <sys/mman.h>
#	include <unistd.h>
#	include <sys/types.h>
#	include <sys/stat.h>
#	include <fcntl.h>
#endif

#define FILE_OPEN_READ      1
#define FILE_OPEN_WRITE     2
#define FILE_OPEN_APPEND    4
#define FILE_OPEN_UPDATE    5

#define FILE_TYPE_MEMREAD   1
#define FILE_TYPE_SHM       2
#define FILE_TYPE_MMAP      3
#define FILE_TYPE_FS        4
#define FILE_TYPE_BFS       5

namespace NLP
{
	class CMMapFile
{
public:
	//���캯��
	CMMapFile();
	//��������
	virtual ~CMMapFile();
	/*
	 * ���ļ�
	 * 
	 */ 
	bool open(const char *szFileName, int flag = FILE_OPEN_READ, size_t length = 0);
	/*
	 * ����ӳ���ļ�
	 */
	bool reopen(off_t nOffset, size_t nLength);
	/* 
	 * �ر��ڴ�ӳ���ļ�
	 * ˵����
	 *		���ڴ�ӳ���ļ����浽Ӳ���ļ���
	 *		�ͷź͸ô˲����йص�һ�����ݺ���Դ��
	 */
	bool close();
	/* ��ƫ����ת��Ϊ��ַ */
	inline char *offset2Addr(size_t nOffset) const
	{
		assert(m_pBase!=NULL);
		return (m_pBase + nOffset);
	}
	/* �����ļ���С */
	size_t getSize()
	{
		return m_nLength;
	}
	/* �ڴ�ӳ���ļ����ݱ��ı��,���ô˺�������ͬ������ */
	bool flush();
	// �����ļ�λ��
	bool setPosition(size_t pos, int whence = SEEK_SET);
	// �õ��ļ���ǰλ��
	size_t getPosition();
	// ���ļ�, �����Ƕ����ֽ���
	size_t read(void *src, size_t len);
	// д�ļ�, ������д���ֽ���
	size_t write(void *src, size_t len);
    int getFileType() { return FILE_TYPE_MMAP; }
	char *getFileName() const {
		return m_szFileName;
	}
private:
	/* 
	* ��ĳһ���ļ�ӳ�䵽�ڴ�,bReadOnlyָ�����򿪵��ļ��Ƿ�ֻ���ڶ�,������Խ��ж�д
	* ���ļ��ɹ�����ӳ����ڴ����ַ��ʧ�ܷ���NULL��
	*/
	bool openInternal(const char* pszName, bool bReadOnly = false);
	/*  
	* ����һ��ָ����С���ڴ�ӳ���ļ�,���е����ݶ��������ڴ���,����Ӳ���ϵ�������ӳ��
	* ���أ�
	*		ӳ����ڴ����ַ��ʧ�ܷ���NULL��
	*/
	bool create(const char* pszName, size_t nLength);

private:
	size_t m_nLength;				//�ļ���С
	size_t m_nPos;					//λ��
	char* m_pBase;					//���ݻ�ָ��

	struct SFileHandler				//ʵ��������
	{
#ifdef _WIN32
		HANDLE m_hFile;
		HANDLE m_hMapFile;
#else
		int m_fd;		//�ļ�������
#endif
	};
	struct SFileHandler m_pHander;		    //ʵ�ֶ���ָ��
	char *m_szFileName;
};
}



#endif //MMAPFILE_H
