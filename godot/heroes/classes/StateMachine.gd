extends Node
class_name StateMacine


const KEEP_CURRENT = -1

var current_state:int=-1:
	set(v):
		owner.transition_state(current_state,v)
		current_state=v
		state_time = 0

var state_time:float

func _ready() -> void:
	await owner.ready # 等待owner的eady信号
	current_state = 0

func _physics_process(delta: float) -> void:
	while true:
		var next_state = owner.get_next_state(current_state) as int
		if KEEP_CURRENT == next_state:
			break
		current_state = next_state
	
	owner.tick_physics(current_state,delta)
	state_time += delta
