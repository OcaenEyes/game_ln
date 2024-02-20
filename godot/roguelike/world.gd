extends Node2D
@onready var camera_2d: Camera2D = $Player/Camera2D
@onready var tile_map: TileMap = $TileMap

func _ready() -> void:
	print("游戏开始")
	var used:= tile_map.get_used_rect()
	var tile_size := tile_map.tile_set.tile_size
	
	camera_2d.limit_top = used.position.y * tile_size.y
	camera_2d.limit_right = used.end.x * tile_size.x
	camera_2d.limit_bottom = used.end.y * tile_size.y
	camera_2d.limit_left = used.position.x * tile_size.x
	print(used.position,used.end)
	camera_2d.reset_smoothing() #将相机的位置立即设置为其当前平滑的目标位置
