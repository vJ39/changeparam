changeparam
===========
実行時に渡されたargsを別のプログラムに渡して実行するだけのプログラム。
***
バージョン
----
0.0.4
ソース
--------------
```cmd
git clone https://github.com/v1T5VgfYSXt41fk5/changeparam changeparam
```
設定
----------
exe置いてるDirの __changeparam.ini__（ファイル名固定）を読みます。

```ini
[Settings] 
Command="コマンド名 /opt1 /opt2 "%1" "%2" "%3" "%4""  
Error=0  
Debug=0  
```
__Command__  
全体を __ダブルクォート(")__ で囲む
実行時に受け取るパラメータは __%1～%10__ 。

__Error( 0 | 1 )__  
実行失敗したときにMessageBoxを表示する。

__Debug( 0 | 1 )__  
実行文字列をMessageBoxで表示する。
経緯
---------
[フォルダ内のファイル比較ツール](http://homepage2.nifty.com/nonnon/)の中で使用するdiffツールを同梱の奴じゃなく[WinMerge](http://winmerge.org/.)にしたかった社員がいて、しょうがねえからつくってやった。

ライセンス
-----------
アイコンはビジネスでもつこうていいよっていうフリーのやつ取ってきた。ソース失念。じぶんが作った部分にかんしてはライセンスはないです。

バグ
-----------
Windows8(64bit)上でchangeparam.exeプロセスが終了しないことがあったが、killすれば問題ない。
