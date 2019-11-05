from cocos.director import director
from cocos.sprite import *
from cocos.layer import *
from cocos.scene import *
from cocos.scenes.transitions import *
from intro_menu import IntroMenu
import random
import pyglet
from game_client import GameClient
from game_server import GameServer
import socket 


class Game(object):
    """
    """
    default_title = "Dung Beetle Ball"
    default_window_width = 1024
    default_window_height = 768
    splash_image = pyglet.image.load('dung-beetle-title2.png')
    instance = None
    
    def __init__(self):
        super( Game, self ).__init__()
        
        random.seed()
        serverID = socket.gethostbyname(socket.gethostname())

        director_width = Game.default_window_width
        director_height = Game.default_window_height
        
        background_image_name = 'groundA.png'
        self.background_image = pyglet.resource.image(background_image_name)
        if self.background_image:
            director_width = self.background_image.width
            director_height = self.background_image.height
        else:
            print "Error: Faled to load background image:", \
                background_image_name
        
        print director_width, director_height
        director.init(director_width, director_height,
            caption = Game.default_title + ' ' + serverID)
        
        intro_menu = IntroMenu(self)
        
        splash_sprite = Sprite (Game.splash_image)
        splash_sprite.position = (Game.default_window_width/2,
            Game.default_window_height/2)

        intro_layer = Layer()
        intro_layer.add(intro_menu, z=1)
        intro_layer.add(splash_sprite, z=0)
        
        self.intro_scene = Scene(intro_layer)

    def run(self):
        director.set_show_FPS(True)
        director.run (self.intro_scene)
    
    def on_name( self, value ):
        print(value)

    def on_join_game( self ):
        Game.instance = GameClient(self.background_image)
        director.replace(FadeTRTransition(Game.instance.get_scene(), 2))
        Game.instance.start()

    def on_host_game( self ):
        Game.instance = GameServer(self.background_image)
        director.replace(FadeTRTransition(Game.instance.get_scene(), 2))
        Game.instance.start()

    def on_quit( self ):
        pyglet.app.exit()


if __name__ == "__main__":
    game = Game()
    game.run()
