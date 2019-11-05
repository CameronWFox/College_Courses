import cocos
from cocos.text import Label
from cocos import scene
from cocos.layer import Layer
from cocos.director import director
from cocos.sprite import Sprite


class KeyboardInputLayer(Layer):
    # You need to tell cocos that your layer is for handling input!
    # This is key (no pun intended)!
    # If you don't include this you'll be scratching your head wondering why your game isn't accepting input
    is_event_handler = True

    def __init__(self):
        super(KeyboardInputLayer, self).__init__()

        self.keys_being_pressed = set()

    def on_key_press(self, key, modifiers):
        self.keys_being_pressed.add(key)

    def on_key_release(self, key, modifiers):
        self.keys_being_pressed.remove(key)


