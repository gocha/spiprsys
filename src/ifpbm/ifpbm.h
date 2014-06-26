/**
 * Susie plug-in: Presys PBM Image
 * written by gocha, feel free to redistribute
 * 
 * based on spi00in_ex.h by Shimitei
 * http://www.asahi-net.or.jp/~kh4s-smz/spi/make_spi.html
 */

#ifndef ifpbm_h
#define ifpbm_h

#include <windows.h>
#include "spi00in.h"

#define RSEED_BEYONDP           0x1f7b
#define RSEED_BOM2              0x1e8e
/* �f�R�[�h�Ɏg�������̎� */
#define IFPBM_RSEED             RSEED_BOM2

/*-------------------------------------------------------------------------*/
/* ���� Plugin �̏�� */
/*-------------------------------------------------------------------------*/
static const char *pluginfo[] = {
  "00IN",                       /* Plug-in API �o�[�W���� */
  "Presys PBM",                 /* Plug-in��,�o�[�W�����y�� copyright */
  "*.pbm",                      /* ��\�I�Ȋg���q ("*.JPG" "*.JPG;*.JPEG" �Ȃ�) */
  "Presys PBM Image (*.PBM)",   /* �t�@�C���`���� */
};

#pragma pack(push)
#pragma pack(1) /* �\���̂̃����o���E��1�o�C�g�ɂ��� */
typedef struct TAGPBMFILEHEADER
{
  WORD pbType;
  WORD pbUnknown02;
  WORD pbMaskMode;
  DWORD pbUnknown06;
  DWORD pbUnknown0A;
  DWORD pbUnknown0E;
  DWORD pbUnknown12;
  WORD pbWidth;
  WORD pbUnknown18;
  WORD pbHeight;
  WORD pbUnknown1C;
  WORD pbBitCount;
  WORD pbUnknown20;
  WORD pbCheckSum;
  WORD pbUnknown24;
  DWORD pbUnknown26;
  DWORD pbUnknown2A;
  DWORD pbUnknown2E;
  DWORD pbUnknown32;
} PBMFILEHEADER;
#pragma pack(pop)

/* �w�b�_�`�F�b�N���ɕK�v�ȃT�C�Y.2KB�ȓ���. */
#define HEADBUF_SIZE (sizeof(PBMFILEHEADER))

BOOL APIENTRY SpiEntryPoint(HANDLE hModule, DWORD ul_reason_for_call, LPVOID lpReserved);
BOOL IsSupportedEx(char *filename, char *data);
int GetPictureInfoEx(char *data, struct PictureInfo *lpInfo);
int GetPictureEx(long datasize, HANDLE *pHBInfo, HANDLE *pHBm,
    SPI_PROGRESS lpPrgressCallback, long lData, char *data);

#endif
