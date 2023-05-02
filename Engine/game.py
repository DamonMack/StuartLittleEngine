from bin import StuartLittleEngine as e

class Coin:
    def __init__(self, x, y):
        self.gameobject = e.GameObject()
        self.transform = e.TransformComponent(x, y)
        self.sprite = e.SpriteComponent("./Assets/Coin.txt", self.transform, False)
        self.collect = e.CollectComponent(character_transform, self.transform, self.sprite)
        self.gameobject.addComponent(self.transform)
        self.gameobject.addComponent(self.sprite)
        self.gameobject.addComponent(self.collect)
        game.addGameObject(self.gameobject)

class Enemy:
    def __init__(self, x, y, range, time):
        self.gameobject = e.GameObject()
        self.transform = e.TransformComponent(x, y)
        self.sprite = e.SpriteComponent("./Assets/enemy.txt", self.transform, True)
        self.physics = e.PhysicsComponent(self.transform, tmc, False, self.sprite.getColliderID())
        self.patrol = e.PatrolComponent(range, time, self.transform)
        self.gameobject.addComponent(self.transform)
        self.gameobject.addComponent(self.sprite)
        self.gameobject.addComponent(self.physics)
        self.gameobject.addComponent(self.patrol)
        game.addGameObject(self.gameobject)


class Decoration:
    def __init__(self, x, y, filepath):
        self.gameobject = e.GameObject()
        self.transform = e.TransformComponent(x, y)
        self.sprite = e.SpriteComponent(filepath, self.transform, False)
        self.gameobject.addComponent(self.transform)
        self.gameobject.addComponent(self.sprite)
        game.addGameObject(self.gameobject)


def controlPlayer():
    TERMINAL_VELOCITY = 6
    HOLDING_SPACE_GRAVITY = 0.35
    NOT_HOLDING_SPACE_GRAVITY = 0.6
    JUMP_VELOCITY = -7.5
    X_ACCEL_GROUND = 0.25
    X_ACCEL_AIR = 0.11
    X_TOP_SPEED = 2.5
    
    x = character_controller.getXVelocity()
    y = character_controller.getYVelocity()
    # X Control
    if e.Input.getInstance().isPressingKey("A"):
        x -= X_ACCEL_GROUND if character_controller.isGrounded() else X_ACCEL_AIR
    elif e.Input.getInstance().isPressingKey("D"):
        x += X_ACCEL_GROUND if character_controller.isGrounded() else X_ACCEL_AIR
    else:
        slow_down_amount = X_ACCEL_GROUND if character_controller.isGrounded() else X_ACCEL_AIR
        if x > 0: slow_down_amount *= -1
        x += slow_down_amount
    x = max(-X_TOP_SPEED, min(x, X_TOP_SPEED))
    # Y Control
    if not character_controller.isGrounded():
        y += HOLDING_SPACE_GRAVITY if e.Input.getInstance().isPressingKey("Space") else NOT_HOLDING_SPACE_GRAVITY
        if y > TERMINAL_VELOCITY:
            y = TERMINAL_VELOCITY
    if e.Input.getInstance().isPressingKey("Space") and character_controller.isGrounded():
        y = JUMP_VELOCITY
    character_controller.setVelocity(x, y)
    # Animation
    if e.Input.getInstance().isPressingKey("A"):
        character_run_sprite.setFlipped(True)
        character_jump_sprite.setFlipped(True)
        character_idle_sprite.setFlipped(True)
    if e.Input.getInstance().isPressingKey("D"):
        character_run_sprite.setFlipped(False)
        character_jump_sprite.setFlipped(False)
        character_idle_sprite.setFlipped(False)
    global JumpState
    global RunState
    if character_controller.isGrounded():
        JumpState = False
    if e.Input.getInstance().isPressingKey("Space"):
        JumpState = True
    if character_controller.getYVelocity() > 3:
        JumpState = True
    RunState = e.Input.getInstance().isPressingKey("A") or e.Input.getInstance().isPressingKey("D")


def considerRespawn():
    # Fall Death
    if character_transform.getY() > 800 or e.Input.getInstance().isPressingKey("R"):
        character_transform.setX(128)
        character_transform.setY(500)
    # Enemy Death
    for enemy in enemies:
        if e.ColliderManager.getInstance().colliding(character_run_sprite.getColliderID(), enemy.sprite.getColliderID()):
            character_transform.setX(128)
            character_transform.setY(500)

def getJumpState():
    return JumpState

def getRunState():
    return RunState

def controlCamera():
    if e.Input.getInstance().isPressingKey("Up"):
        character_cam_focus.updateZoomBy(1 * 0.016)
    if e.Input.getInstance().isPressingKey("Down"):
        character_cam_focus.updateZoomBy(-1 * 0.016)

game = e.Engine()
game.initGraphics()

# Background GameObjects
cloud = Decoration(150, 550, "./Assets/cloud.txt")
cloud2 = Decoration(364, 514, "./Assets/cloud.txt")
cloud3 = Decoration(650, 550, "./Assets/cloud.txt")
cloud4 = Decoration(760, 600, "./Assets/cloud.txt")
cloud5 = Decoration(850, 480, "./Assets/cloud.txt")
cloud6 = Decoration(930, 570, "./Assets/cloud.txt")
cloud7 = Decoration(1100, 500, "./Assets/cloud.txt")
cloud8 = Decoration(1230, 560, "./Assets/cloud.txt")

bush = Decoration(200, 688, "./Assets/bush.txt")
bush2 = Decoration(550, 688, "./Assets/bush.txt")
bush3 = Decoration(950, 688, "./Assets/bush.txt")

# Active GameObjects
tilemap = e.GameObject()
character = e.GameObject()

tmc = e.TileMapComponent("./Assets/TestMarioLevel.txt")

character_transform = e.TransformComponent(128, 500)
character_run_sprite = e.SpriteComponent("./Assets/MarioRun.txt", character_transform, True)
character_idle_sprite = e.SpriteComponent("./Assets/MarioIdle.txt", character_transform, False)
character_jump_sprite = e.SpriteComponent("./Assets/MarioJump.txt", character_transform, False)
character_physics = e.PhysicsComponent(character_transform, tmc, False, character_run_sprite.getColliderID())
character_controller = e.ControllerComponent(character_physics)
character_cam_focus = e.CameraFocusComponent(character_transform, 0.35, 0.45, 0.06, 3)
character_anim = e.AnimatorComponent()
JumpState = False
RunState = False
character_anim.addSprite(character_jump_sprite, lambda: getJumpState())
character_anim.addSprite(character_run_sprite, lambda: getRunState())
character_anim.addSprite(character_idle_sprite, lambda: True)

tilemap.addComponent(tmc)

character.addComponent(character_transform)
character.addComponent(character_anim)
character.addComponent(character_physics)
character.addComponent(character_controller)
character.addComponent(character_cam_focus)

game.addGameObject(tilemap)
game.addGameObject(character)

coin = Coin(216, 650)
coin2 = Coin(232, 634)
coin3 = Coin(248, 618)
coin4 = Coin(320, 550)
coin5 = Coin(336, 550)
coin6 = Coin(352, 550)
coin7 = Coin(435, 520)
coin8 = Coin(451, 520)
coin9 = Coin(467, 520)

enemy = Enemy(527, 688, 82, 1)
enemy2 = Enemy(752, 688, 98, 1)
enemies = [enemy, enemy2]

# Run Game
while not e.Input.getInstance().gotQuitInput():
    game.input(False) # todo remove parameter
    controlPlayer()
    considerRespawn()
    controlCamera()
    game.update(16)
    game.render()
    game.delay(16)

game.shutDown()
