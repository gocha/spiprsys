Susie plugin for Presys games (spiprsys)
========================================

spiprsys is a Susie plugin package for [Presys](http://www.presys.jp/) games.

- **ifpbm.spi**: Decoder plugin for PBM image format

Presys' games are programmed in HSP, and resources files are often embedded as DPM archive (HSP's archive format). Get [spihsp](https://github.com/gocha/spihsp) to unpack the DPM archive.

What is Susie plugin?
------------------------

[Susie](http://www.digitalpad.co.jp/~takechin/) is an old-school picture viewer for Windows, which can load additional formats by adding Susie plugins (*.spi). In Japan, Susie plugin is often used for decoding custom image formats inside a game.

There are several picture viewers that supports Susie plugin. For example:

- [Susie](http://www.digitalpad.co.jp/~takechin/betasue.html#susie32)
- [Linar](http://hp.vector.co.jp/authors/VA015839/)
- [picture effecter](http://www.asahi-net.or.jp/~DS8H-WTNB/software/index.html)
- [stereophotomaker](http://stereo.jpn.org/eng/stphmkr/)
- [vix](http://www.forest.impress.co.jp/library/software/vix/)
- [A to B converter](http://www.asahi-net.or.jp/~KH4S-SMZ/spi/abc/index.html)
- [ACDSee](http://www.acdsee.com/) (commercial)

My favorite is [Linar](http://hp.vector.co.jp/authors/VA015839/) for browsing, and [AtoB Converter](http://www.asahi-net.or.jp/~kh4s-smz/spi/abc/) for batch conversion.

Note
------------------------

- Any use of the software is entirely at your own risk.

File Format
------------------------

The PBM format is mostly identical with popular Windows Bitmap, except several header fields and a simple encryption.

See the Susie plugin's header file for the structure of the file header.

PBM format has bitdepth field in the header, but it must be less or equal to 8 as far as I know. (i.e. an indexed color image)

Palette entry is ciphered by a randomizer.
It just uses HSP's build-in RNG (in other words, VC++ rand function),
but the randomseed is specific to each game, and it's impossible to extract it from the image file.

Therefore, the Susie plugin hardcodes the randomseed value. Silly!
You might want to use [HSP Decompiler](http://sourceforge.jp/projects/hspdeco/) to extract the randomseed from a new game.

Digression
------------------------

Presys' "Bombaran" is the Windows game I have played for the first time.
After few months, I have started learning a programming. I wanted to create my own game.

Presys, thank you for giving a chance to start my programming life.
You gave me even a chance to start my reverse-engineering life. Thank you very much.

Hope I will meat your new fun game, someday.
