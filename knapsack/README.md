# ナップサック問題 
ナップサック問題とは，簡単にいうと与えられた入力と制約のもとで目的関数を最大化する問題のことです．
動的計画法を用いて最大値と組み合わせを出力します．
##例題
長さ`L`の金属棒が与えられるとして，この金属棒を切断したそれぞれ`(l_i * x_i)`を売りたい状況を考えます．
このとき，切り出した金属棒の長さに応じて，売るときの価格が分かっていて，切り出した金属棒の価格の合計を最も高くしたいとします．
この状況をナップサック問題に置き換えると，

* 入力 `切り出す長さと価格`:`InputSet[i].length, InputSet[i].price`
* 制約 `切り出した長さの合計 < L`
* 目的関数 `切り出した金属棒の価格の合計`

となります．
同じ長さの切り出しはOKなので，これは個数制限無しのナップサック問題になります．
####入力例

<table>
    <tr>
        <td>長さ</td>
        <td>1</td>
        <td>2</td>
        <td>3</td>
        <td>4</td>
        <td>5</td>
        <td>6</td>
        <td>7</td>
        <td>8</td>
        <td>9</td>
        <td>10</td>
    </tr>
    <tr>
        <td>価格</td>
        <td>1</td>
        <td>5</td>
        <td>8</td>
        <td>9</td>
        <td>10</td>
        <td>17</td>
        <td>17</td>
        <td>20</td>
        <td>24</td>
        <td>30</td>
    </tr>
</table>

##アルゴリズム
動的計画法を用いて実装しています．

[knapsack.cpp][link_knapsack]を参照してください．

`>knapsack [number]`で`0<L<=number`の結果を出力します．

##出力

`0 < L <= 20`のときの出力結果→[result_20.dat][link_result]．

[link_knapsack]:https://github.com/romancek/algorithm/blob/master/knapsack/knapsack.cpp "実装のリンク"
[link_result]:https://github.com/romancek/algorithm/blob/master/knapsack/result_20.dat "出力例のリンク"
