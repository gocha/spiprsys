/**
 * SUSIE32 '00IN' Plug-in Sample by shimitei (modified by gocha)
 * http://www.asahi-net.or.jp/~kh4s-smz/spi/make_spi.html
 */

#ifndef spi00in_h
#define spi00in_h

#include <windows.h>

/*-------------------------------------------------------------------------*/
/* �摜���\���� */
/*-------------------------------------------------------------------------*/
#pragma pack(push)
#pragma pack(1) /* �\���̂̃����o���E��1�o�C�g�ɂ��� */
typedef struct PictureInfo
{
  long left,top;        /* �摜��W�J����ʒu */
  long width;           /* �摜�̕�(pixel) */
  long height;          /* �摜�̍���(pixel) */
  WORD x_density;       /* ��f�̐����������x */
  WORD y_density;       /* ��f�̐����������x */
  short colorDepth;     /* ��f�������bit�� */
  HLOCAL hInfo;         /* �摜���̃e�L�X�g��� */
} PictureInfo;
#pragma pack(pop)

/*-------------------------------------------------------------------------*/
/* �G���[�R�[�h */
/*-------------------------------------------------------------------------*/
#define SPI_NO_FUNCTION         -1  /* ���̋@�\�̓C���v�������g����Ă��Ȃ� */
#define SPI_ALL_RIGHT           0   /* ����I�� */
#define SPI_ABORT               1   /* �R�[���o�b�N�֐�����0��Ԃ����̂œW�J�𒆎~���� */
#define SPI_NOT_SUPPORT         2   /* ���m�̃t�H�[�}�b�g */
#define SPI_OUT_OF_ORDER        3   /* �f�[�^�����Ă��� */
#define SPI_NO_MEMORY           4   /* �������[���m�ۏo���Ȃ� */
#define SPI_MEMORY_ERROR        5   /* �������[�G���[ */
#define SPI_FILE_READ_ERROR     6   /* �t�@�C�����[�h�G���[ */
#define SPI_WINDOW_ERROR        7   /* �����J���Ȃ� (����J�̃G���[�R�[�h) */
#define SPI_OTHER_ERROR         8   /* �����G���[ */
#define SPI_FILE_WRITE_ERROR    9   /* �������݃G���[ (����J�̃G���[�R�[�h) */
#define SPI_END_OF_FILE         10  /* �t�@�C���I�[ (����J�̃G���[�R�[�h) */

/*-------------------------------------------------------------------------*/
/* '00IN'�֐��̃v���g�^�C�v�錾 */
/*-------------------------------------------------------------------------*/
typedef int (CALLBACK *SPI_PROGRESS)(int, int, long);
  int __declspec(dllexport) __stdcall GetPluginInfo
      (int infono, LPSTR buf, int buflen);
  int __declspec(dllexport) __stdcall IsSupported(LPSTR filename, DWORD dw);
  int __declspec(dllexport) __stdcall GetPictureInfo
      (LPSTR buf,long len, unsigned int flag, PictureInfo *lpInfo);
  int __declspec(dllexport) __stdcall GetPicture
      (LPSTR buf,long len, unsigned int flag,
       HANDLE *pHBInfo, HANDLE *pHBm,
       SPI_PROGRESS lpPrgressCallback, long lData);
  int __declspec(dllexport) __stdcall GetPreview
      (LPSTR buf,long len, unsigned int flag,
       HANDLE *pHBInfo, HANDLE *pHBm,
       SPI_PROGRESS lpPrgressCallback, long lData);

#endif
