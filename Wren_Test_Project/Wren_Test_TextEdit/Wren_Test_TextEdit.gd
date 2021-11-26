extends Control

var wren_manager : WrenManager;
var text_edit : TextEdit;

func _ready():
	wren_manager = get_node("WrenManager");
	text_edit = get_node("TextEdit");
	
	wren_manager.initialize();
	wren_manager.set_code_string(text_edit.text);
