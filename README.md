# FixpointCodingTest
## 実行方法
```
make
./main N1 m t N2 < inputFile
```
## inputFile のフォーマット
inputFileのフォーマット: 確認日時, IPv4アドレス, 応答時間
また、確認日時は時系列で並んでいると仮定する。
以下説明:
確認日時は、YYYYMMDDhhmmssの形式。ただし、年＝YYYY（4桁の数字）、月＝MM（2桁の数字。以下同様）、日＝DD、時＝hh、分＝mm、秒＝ssである。
サーバアドレスは、ネットワークプレフィックス長付きのIPv4アドレスである。
応答結果には、pingの応答時間がミリ秒単位で記載される。ただし、タイムアウトした場合は"-"(ハイフン記号)となる。

以下に監視ログの例（抜粋）を示す。

20201019133124,10.20.30.1/16,2
20201019133125,10.20.30.2/16,1
20201019133134,192.168.1.1/24,10
20201019133135,192.168.1.2/24,5
20201019133224,10.20.30.1/16,522
20201019133225,10.20.30.2/16,1
20201019133234,192.168.1.1/24,8
20201019133235,192.168.1.2/24,15
20201019133324,10.20.30.1/16,-
20201019133325,10.20.30.2/16,2

## 出力ファイルのフォーマット
タイムアウトの場合, timeOut: IPv4アドレス: [begin, end)
timeOutが現在まで続いている場合, [begin, ) と表示する。
過負荷の場合, overLoaded: IPv4アドレス: [begin, end)
overLoadedが現在まで続いている場合, [begin, ) と表示する。
## テスト
google test に依存しています: https://github.com/google/googletest
```
make LD_test
./LD_test
```
