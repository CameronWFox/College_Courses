from intro_menu import IntroMenu

from cocos.layer import *
from cocos.scene import *
from cocos.actions import *
from cocos.director import director
from cocos.sprite import *
from cocos.scenes.transitions import *

import sys
from time import sleep, localtime
from weakref import WeakKeyDictionary

from PodSixNet.Server import Server
from PodSixNet.Channel import Channel

class ClientChannel(Channel):
	"""
	This is the server representation of a single connected client.
	"""
	def __init__(self, *args, **kwargs):
		self.nickname = "anonymous"
		Channel.__init__(self, *args, **kwargs)
	
	def Close(self):
		self._server.DelPlayer(self)
	
	##################################
	### Network specific callbacks ###
	##################################
	
	def Network_message(self, data):
		self._server.SendToAll({"action": "message", "message": data['message'], "who": self.nickname})
	
	def Network_nickname(self, data):
		self.nickname = data['nickname']
		self._server.SendPlayers()

class ChatServer(Server):
	channelClass = ClientChannel
	
	def __init__(self, *args, **kwargs):
		Server.__init__(self, *args, **kwargs)
		self.players = WeakKeyDictionary()
		print 'Server launched'
	
	def Connected(self, channel, addr):
		self.AddPlayer(channel)
	
	def AddPlayer(self, player):
		print "New Player" + str(player.addr)
		self.players[player] = True
		self.SendPlayers()
		print "players", [p for p in self.players]
	
	def DelPlayer(self, player):
		print "Deleting Player" + str(player.addr)
		del self.players[player]
		self.SendPlayers()
	
	def SendPlayers(self):
		self.SendToAll({"action": "players", "players": [p.nickname for p in self.players]})
	
	def SendToAll(self, data):
		[p.Send(data) for p in self.players]
	
	def Launch(self):
		while True:
			self.Pump()
			sleep(0.0001)

class ServerNetworkAction(Action):
    """ 
    
    """
    def init(self, game):
        self.game = game
    
    def start(self):
        host, port = sys.argv[1].split(":")
        self.server = ChatServer(localaddr=(host, int(port)))
        print 'GameServer start'
    
    def step(self, dt):
        """ Each time the layer is "stepped", give the networking
            subsystem a chance to respond to messages from clients. 
        """
        self.server.Pump()

class GameServer:

    def __init__(self):
        splash_image = pyglet.image.load('dung-beetle-title2.png')
        splash_sprite = Sprite (splash_image)
        splash_sprite.position = (640/2,
            480/2)

        self.intro_layer = Layer()
        self.intro_layer.add(splash_sprite, z=0)

        self.intro_scene = Scene(self.intro_layer)
    
    def go(self):

        self.intro_layer.do(ServerNetworkAction(None))

        director.set_show_FPS(True)
        director.run (self.intro_scene)


class Game:

    def go(self):
        director.init(
            640,
            480,
            caption = "Fubar")

        splash_image = pyglet.image.load('dung-beetle-title2.png')
        splash_sprite = Sprite (splash_image)
        splash_sprite.position = (640/2,
            480/2)

        intro_menu = IntroMenu(self)

        intro_layer = Layer()
        intro_layer.add(intro_menu, z=1)
        intro_layer.add(splash_sprite, z=0)

        intro_scene = Scene(intro_layer)

        self.server = GameServer()
        
        director.set_show_FPS(True)
        director.run (intro_scene)

    def on_name( self, value ):
        print(value)

    def on_join_game( self ):
        pass
    
    def on_host_game( self ):
        director.replace(FadeTRTransition(self.server.intro_scene, 2))
        self.server.go()

    def on_quit( self ):
        pyglet.app.exit()

if __name__ == "__main__":
    g = Game()
    g.go()
