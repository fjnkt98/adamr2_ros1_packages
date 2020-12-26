# adamr2_description

## Abstract

このパッケージは，ロボットの構造を記述するためのフォーマットであるURDF(Unified Robot Description Format)を定義するためのパッケージです．  
URDFを直接書くのは面倒なので，[xacro](http://wiki.ros.org/xacro)を使ってプログラマブルに記述しています．

このパッケージの`urdf/`ディレクトリ内にADAMR2の構造を記述したxacroファイルが格納されています．  
`meshes/`ディレクトリにはロボットの見た目を表すためのSTLファイルが格納されています．  
また，`launch/`ディレクトリにはロボットの見た目を確認するためのlaunchファイルが置かれています．

## Robot Models

このパッケージでは，いくつかの目的のために複数URDFモデルのバリエーションを用意しています．

- 実機動作用
- シミュレーション動作用
- 実機のbagファイル再生時用

これらのバリエーションは，トップレベルのxacroファイルを変更することによって実現しているため，各部品のxacroファイルは(一部の物を除いて)共通のものが使用されています．

### 実機動作用モデル

ロボットの実機を動作させる際に使用するロボットモデルです．  
このモデルでは，自在キャスターに繋がっている回転ジョイントを全て固定ジョイントに設定しています．
これは，実機動作時にはキャスターの回転角を取得することができないため，リンク間の状態をROS側が認識できず，それによりTFのエラーが生じるためです．
これを回避するため，キャスターのジョイントを回転ジョイントではなく固定ジョイントに設定しています．  

### シミュレーション動作用

Gazeboシミュレーション時に使用するロボットモデルです．  
このモデルでは，キャスターリンクの取り付け位置を実際よりもわずかに(2.7mm)下げ，前後のキャスターが常に接地し，ロボットの姿勢が水平を保つように設定しています．
本来は実機と同様に，キャスターを浮かせてシミュレーションするべきなのですが，シミュレーションでは駆動輪の変形や軸のたわみが無いため，ロボットの姿勢は必ず前後どちらかに傾きます．
ロボットの姿勢がわずかに傾くと，シミュレータのレーザースキャンデータに無視できない程のノイズが発生してしまうという問題が発生しました(原因は不明です)．
そのため，このような処置をとっています．

### 実機のbagファイル再生時用

このモデルでは，URDFの中に[realsense2_description](http://wiki.ros.org/realsense2_camera)のリンクを組み込み，デバイスの内部リンクの位置関係を保持するように設定しています．  
Realsense D435は内部に複数のリンクを持っており，画像トピックやPointCloudトピックはそれぞれのリンクを基準として配信されます．
実機動作時はドライバノードが静的なTFを発行して位置関係を配信しており，bagファイルには`tf_static`トピックに記録されます．
この`tf_static`トピックはbagファイル再生直後のタイミングに1度のみ配信されます．
bagファイルの最初から最後まで全てのデータを使用する際は問題無いのですが，例えばbagファイル再生から一定時間経った後のデータだけ使いたいという場合には，`tf_static`トピックを受信できないため，リンクの位置関係はURDFを使って取得しなければなりません．
そのような用途のためにこのロボットモデルを作成しています．

## Links

ロボットは以下の表に示すリンクを持っています．

| name | description |
| ---- | ----------- |
| base_footprint| 最上位リンク．base_linkの真下，地面と同じ高さに位置する |
| base_link | ロボットのボディのリンク．フレームが作る長方形の中心に位置する |
| right_wheel_link | 右車輪リンク |
| left_wheel_link | 左車輪リンク |
| front_caster_support_link | 前方キャスターのサポート |
| front_caster_wheel_link | 前方キャスターのホイール |
| back_caster_support_link | 後方キャスターのサポート |
| back_caster_wheel_link | 後方キャスターのホイール |
| lidar_link | LiDARのリンク |
| camera_link| Realsenseのリンク |

## Parent-tree

各リンクの親子関係は以下のようになっています．

```generic
base_footprint
  └ base_link
      ├ right_wheel_link
      ├ left_wheel_link
      ├ front_caster_support_link
      │    └ front_caster_wheel_link
      ├ back_caster_support_link
      │    └ back_caster_wheel_link
      ├ lidar_link
      └ camera_link
```

## Launch file

パッケージには以下のlaunchファイルが存在します．

- `display.launch` : モデルの表示用launchファイル
- `adamr2_description`: `robot_description`パラメータ配信用launchファイル

### display.launch

URDFの記述が正しいかどうかを確認するために，ロボットモデルをrvizで表示するだけのlaunchファイルです．  
実行することで，rvizが起動し，ロボットのモデルが表示されます．

```bash
roslaunch adamr2_description display.launch
```

### adamr2_description.launch

ロボットのリンクの位置関係を`robot_description`に登録するためのlaunchファイルです．  
bagファイル再生時に使用することで，TFのエラーを回避します．

```bash
roslaunch adamr2_description adamr2_description.launch
```
