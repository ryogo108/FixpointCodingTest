# FixpointCodingTest
## 実行方法
```
make
./main N1 m t N2 < inputFile
```
設問とコマンドライン引数との対応:
設問1: 対応なし
設問2: N1
設問3: m t
設問4: N2
## 
## 入力フォーマット
inputFileのフォーマット: 確認日時, IPv4アドレス, 応答時間
また、確認日時は時系列で並んでいると仮定する。
## 出力フォーマット
Prob1:
timeOut: IPv4アドレス: [begin, end) の羅列
Prob2:
timeOut: IPv4アドレス: [begin, end) の羅列
Prob3:
overLoaded: IPv4アドレス: [begin, end) の羅列
Prob4:
timeOut in the subnet Subnet: [begin, end) の羅列
## テスト
google test に依存しています: https://github.com/google/googletest
```
make LD_test
./LD_test
```
