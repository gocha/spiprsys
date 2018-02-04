Susie plugin for Presys games (spiprsys)
========================================
[![AppVeyor Build Status](https://ci.appveyor.com/api/projects/status/h9e6u2ugpj1ueume/branch/master?svg=true)](https://ci.appveyor.com/project/gocha/spiprsys/branch/master)

spiprsys は [Presys](http://www.presys.jp/) 製ゲーム向けの Susie プラグインパッケージです。

- **ifpbm.spi**: Decoder plugin for PBM image format

Presys のゲームは HSP 製で、リソースファイルは大抵 DPM アーカイブ（HSP のアーカイブ形式）として埋め込まれています。DPM アーカイブを展開するには [spihsp](https://github.com/gocha/spihsp) を入手してください。

Susie プラグインとは？
------------------------

[Susie](http://www.digitalpad.co.jp/~takechin/) は昔ながらの Windows 向けの画像ビューアです。Susie プラグイン（*.spi）と呼ばれるファイルを追加することで対応フォーマットを増やすことができます。国内ではよくゲーム内部のカスタム画像フォーマットをデコードするのに Susie プラグインが使われます。

Susie プラグインに対応した画像ビューアはいくつか存在します。

- [Susie](http://www.digitalpad.co.jp/~takechin/betasue.html#susie32)
- [Linar](http://hp.vector.co.jp/authors/VA015839/)
- [picture effecter](http://www.asahi-net.or.jp/~DS8H-WTNB/software/index.html)
- [stereophotomaker](http://stereo.jpn.org/eng/stphmkr/)
- [vix](http://www.forest.impress.co.jp/library/software/vix/)
- [A to B converter](http://www.asahi-net.or.jp/~KH4S-SMZ/spi/abc/index.html)
- [ACDSee](http://www.acdsee.com/) (commercial)

わたしのお気に入りは、閲覧目的なら [Linar](http://hp.vector.co.jp/authors/VA015839/)、一括変換目的なら [AtoB Converter](http://www.asahi-net.or.jp/~kh4s-smz/spi/abc/) です。

注意事項・備考など
------------------------

- 本ツールを用いたことによる、いかなる損害やトラブルについても作者は責任を負いません。

ファイルフォーマット
------------------------

若干のヘッダ項目と簡易な暗号化の存在を除けば、PBM フォーマットは Windows ビットマップとほぼ同等です。

ファイルヘッダの構造については Susie プラグインのヘッダーファイルをご覧ください。

ヘッダにはビット深度の項目がありますが、わたしの知る限りは8以下の値を取ります。（つまり、インデックスカラー画像）

パレットエントリは乱数で暗号化されています。
単に HSP 内蔵の乱数生成器（VC++ の rand 関数）が使用されていますが、
乱数の種は各ゲーム固有の値であり、画像ファイルからは取り出すことができません。

なので、Susie プラグインは乱数の種をハードコーディングしています。おばか！
もしかしたら [HSP 逆コンパイラ](http://sourceforge.jp/projects/hspdeco/) を使って、新しいゲームから乱数の種を取り出したくなることがあるかもしれません。

余談
------------------------

Presys の「ぼんばらん」はわたしが初めて遊んだ Windows ゲームです。
数カ月後、わたしはゲームを作りたくなって、プログラミングを学び始めました。

プログラミングを始める重要な機会を与えてくださってありがとうございます。
また、リバースエンジニアリングを学ぶキッカケも頂いてしまったこと、重ねて感謝しています。

また楽しい新作に出会えますように。
