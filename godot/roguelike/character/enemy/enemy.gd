@icon("res://assets/enemies/goblin/goblin_idle_anim_f0.png")
extends BaseCharacter
class_name Enemy

@export var speed:int =50
@export var life:int =5
@export var damage:int=1

@onready var player:CharacterBody2D = get_tree().current_scene.get_node("Player")
@onready var navigation_agent_2d: NavigationAgent2D = $Node2D/NavigationAgent2D
@onready var hurt_box: HurtBox = $HurtBox
@onready var hit_box: HitBox = $HitBox

var force_back_velocity:Vector2 = Vector2.ZERO


func _ready() -> void:
	animated_sprite_2d.play("idle")

func _on_timer_timeout() -> void:
	navigation_agent_2d.target_position = player.global_position
	#print("player.global_position",player.global_position)
	#print("player.position",player.position)
	
func  _physics_process(delta: float) -> void:
	if life<=0:
		hit_box.monitoring = false
		hurt_box.monitorable = false
		var tween:= create_tween()
		tween.set_ease(Tween.EASE_IN).set_trans(Tween.TRANS_LINEAR)
		tween.tween_property(self,"scale",Vector2.ZERO,0.5).from(Vector2.ONE)
		tween.tween_callback(queue_free)
	else:
		var direction: = to_local(navigation_agent_2d.get_next_path_position()).normalized()
		#print("navigation_agent_2d.get_next_path_position()",navigation_agent_2d.get_next_path_position())
		#print("to_local(navigation_agent_2d.get_next_path_position())",to_local(navigation_agent_2d.get_next_path_position()))
		#print("to_global(navigation_agent_2d.get_next_path_position())",to_global(navigation_agent_2d.get_next_path_position()))
		#velocity = direction * speed
		#move_and_slide()
		#print("导航走向player的方向:", direction)
		navigation_agent_2d.velocity =  force_back_velocity if force_back_velocity != Vector2.ZERO else direction * speed 
		force_back_velocity = Vector2.ZERO
		

func _on_navigation_agent_2d_velocity_computed(safe_velocity: Vector2) -> void:
	#print("计算出避障速度发出通知")
	velocity = safe_velocity
	animated_sprite_2d.play("run")
	move_and_slide()


func _on_hurt_box_hurt(hit_source: HitBox) -> void:
	print("父类被layer打了： ",hit_source)
	life -= hit_source.damage
	hit_source.knock_back_direction =   hit_source.global_position.direction_to(global_position).normalized()
	#print("击退方向：",hit_source.knock_back_direction)
	force_back_velocity =  hit_source.knock_back_force * hit_source.knock_back_direction
	#print("击退速度",force_back_velocity)
	var tween := create_tween()
	tween.set_ease(Tween.EASE_OUT_IN ).set_trans(Tween.TRANS_LINEAR)
	#print(self_modulate)
	#print(modulate)
	tween.tween_property(self,"modulate",Color(1, 0.388235, 0.278431, 1),0.2)
	tween.tween_property(self,"modulate",Color(1,1,1,1),0.2)
	
	
	
