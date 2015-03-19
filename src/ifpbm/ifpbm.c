/**
 * Susie plug-in: Presys PBM Image
 * written by gocha, feel free to redistribute
 * 
 * based on spi00in_ex.c by Shimitei
 * http://www.asahi-net.or.jp/~kh4s-smz/spi/make_spi.html
 */

#include <windows.h>
#include <stdlib.h>
#include "ifpbm.h"
#include "hsp2rnd.h"

/* DIB DWORD ALIGNMENT */
#define bmp32pitch(width, bpp)  (((width*bpp+31)>>3)&~3)

/**
 * �G���g���|�C���g
 */
BOOL APIENTRY SpiEntryPoint(HANDLE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
  switch (ul_reason_for_call)
  {
  case DLL_PROCESS_ATTACH:
    break;

  case DLL_THREAD_ATTACH:
    break;

  case DLL_THREAD_DETACH:
    break;

  case DLL_PROCESS_DETACH:
    break;
  }
  return TRUE;
}

/**
 * �t�@�C���擪2KB�ȓ�����Ή��t�H�[�}�b�g�����f
 * (���f�Ɏg�p����T�C�Y�̓w�b�_�t�@�C���Œ�`)
 * �t�@�C���������f�ޗ��Ƃ��ēn����Ă���݂���
 */
BOOL IsSupportedEx(char *filename, char *data)
{
  PBMFILEHEADER* pbmHead = (PBMFILEHEADER*) data;
  WORD pbmMaskMode = pbmHead->pbMaskMode;
  WORD pbmCheckSum = pbmHead->pbCheckSum;
  WORD pbmActualSum;
  WORD rseed = 0;
  Hsp2Rnd* rnd;
  int i;

  /* �V�O�l�`�����m�F */
  if(pbmHead->pbType != 0x6270) /* "pb" */
  {
    return FALSE;
  }

  /* �}�X�N�̎�ʂ��m�F */
  if(pbmMaskMode < 0 || pbmMaskMode > 2)
  {
    return FALSE;
  }
  if(pbmMaskMode == 2)
  {
    rseed = IFPBM_RSEED;
  }

  /* 8�r�b�g�J���[�̂ݑΉ� */
  if(pbmHead->pbBitCount != 8)
  {
    return FALSE;
  }

  /* �`�F�b�N�T�����m�F */
  pbmActualSum = 0;
  if(pbmMaskMode != 0)
  {
    rnd = hsp2RndCreate(rseed);
    if(!rnd) return FALSE;

    for(i = 0; i < 256; i++)
    {
      pbmActualSum += hsp2Rnd(rnd, 256);
    }
    pbmActualSum &= 0xff;
    hsp2RndDelete(rnd);
  }

  if(pbmActualSum != pbmCheckSum)
  {
    return FALSE;
  }

  return TRUE;
}

/*
 * �t�@�C���C���[�W����摜�̏����擾
 * (�o�b�t�@�T�C�Y�̓w�b�_�t�@�C���Œ�`)
 */
int GetPictureInfoEx(char *data, struct PictureInfo *lpInfo)
{
  PBMFILEHEADER* pbmHead = (PBMFILEHEADER*) data;

  lpInfo->left          = 0;
  lpInfo->top           = 0;
  lpInfo->width         = pbmHead->pbWidth;
  lpInfo->height        = pbmHead->pbHeight;
  lpInfo->x_density     = 0;
  lpInfo->y_density     = 0;
  lpInfo->colorDepth    = pbmHead->pbBitCount;
  lpInfo->hInfo         = NULL;

  return SPI_ALL_RIGHT;
}

/*
 * �摜�t�@�C����DIB�ɕϊ�
 * data�̓t�@�C���C���[�W��,�T�C�Y��datasize�o�C�g.
 */
int GetPictureEx(long datasize, HANDLE *pHBInfo, HANDLE *pHBm,
			 SPI_PROGRESS lpPrgressCallback, long lData, char *data)
{
  int result = SPI_ALL_RIGHT;
  PBMFILEHEADER* pbmHead = (PBMFILEHEADER*) data;
  WORD width = pbmHead->pbWidth;
  WORD height = pbmHead->pbHeight;
  WORD bpp = pbmHead->pbBitCount;
  DWORD imageSize = bmp32pitch(width, bpp) * height;
  int i;

  if((size_t) datasize >= (sizeof(PBMFILEHEADER) + (sizeof(RGBQUAD) * 256) + imageSize))
  {
    *pHBInfo = LocalAlloc(LMEM_MOVEABLE, sizeof(BITMAPINFOHEADER) + (sizeof(RGBQUAD) * 256));
    if(*pHBInfo)
    {
      *pHBm = LocalAlloc(LMEM_MOVEABLE, imageSize);
      if(*pHBm)
      {
        BITMAPINFO* bmpinfo = (BITMAPINFO*) LocalLock(*pHBInfo);
        BYTE* bmp = (BYTE*) LocalLock(*pHBm);

        if(bmpinfo && bmp)
        {
          BITMAPINFOHEADER* bmih = (BITMAPINFOHEADER*) bmpinfo;
          RGBQUAD* palette = bmpinfo->bmiColors;
          WORD maskMode = pbmHead->pbMaskMode;
          WORD rseed = 0;
          BYTE sh = 0;
          Hsp2Rnd* rnd;
          RGBQUAD* pbmPals = (RGBQUAD*) (pbmHead + 1);
          BYTE* pbmBits = (BYTE*) (pbmPals + 256);

          /* �摜�̏����i�[ */
          bmih->biSize            = sizeof(BITMAPINFOHEADER);
          bmih->biWidth           = width;
          bmih->biHeight          = height;
          bmih->biPlanes          = 1;
          bmih->biBitCount        = bpp;
          bmih->biCompression     = BI_RGB;
          bmih->biSizeImage       = imageSize;
          bmih->biXPelsPerMeter   = 0;
          bmih->biYPelsPerMeter   = 0;
          bmih->biClrUsed         = 0;
          bmih->biClrImportant    = 0;

          if(maskMode == 2)
          {
            rseed = IFPBM_RSEED;
          }
          rnd = hsp2RndCreate(rseed);
          if(rnd)
          {
            /* �p���b�g���f�R�[�h */
            for(i = 0; i < 256; i++)
            {
              if(maskMode != 0)
              {
                sh = hsp2Rnd(rnd, 256);
              }

              palette[i].rgbBlue  = pbmPals[i].rgbBlue - sh;
              palette[i].rgbGreen = pbmPals[i].rgbGreen - sh;
              palette[i].rgbRed   = pbmPals[i].rgbRed - sh;
            }
            hsp2RndDelete(rnd);

            /* �摜��W�J */
            memcpy(bmp, pbmBits, imageSize);
          }
          else
          {
            result = SPI_NO_MEMORY;
          }
        }
        else
        {
          LocalFree(*pHBm);
          *pHBm = NULL;
          LocalFree(*pHBInfo);
          *pHBInfo = NULL;
          result = SPI_MEMORY_ERROR;
        }

        if(*pHBm) LocalUnlock(*pHBm);
      }
      else
      {
        LocalFree(*pHBInfo);
        *pHBInfo = NULL;
        result = SPI_NO_MEMORY;
      }
      if(*pHBInfo) LocalUnlock(*pHBInfo);
    }
    else
    {
      result = SPI_NO_MEMORY;
    }
  }
  else
  {
    result = SPI_OUT_OF_ORDER;
  }

  return result;
}

/*-------------------------------------------------------------------------*/
