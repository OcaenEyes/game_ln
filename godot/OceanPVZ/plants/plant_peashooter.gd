extends Plants

@export_file("*.tscn") var bullet_res
@export var bullet_speed:int = 200

func  _ready():
	super._ready()
	print("豌豆射手初始化了")
	
func plant_action():
	super.plant_action()
	print("豌豆射手发射一枚子弹")
	var bullet = load(bullet_res).instantiate()
	add_child(bullet)
	bullet.position = bullet.position + Vector2(40,-15)
	#print("bullet 加了 Vector2(40,-15).position",bullet.position)
	bullet.linear_velocity= Vector2(bullet_speed,0)
	
	
