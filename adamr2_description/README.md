# adamr2_description

## Links

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

## Parent-tree

```
base_footprint
     │
     └ base_link
           ├ right_wheel_link
           ├ left_wheel_link
           ├ front_caster_support_link
           │    └ front_caster_wheel_link
           ├ back_caster_support_link
           │    └ back_caster_wheel_link
           └ lidar_link
```

## Launch file

- `adamr2_display.launch` ：モデルの表示用launchファイル
