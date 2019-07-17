import pygame
import time
import random

pygame.init()

WIDTH = 480
HEIGHT = 600 # 120 na nagłowek
# 12 czesci
#12 * 12 = 144 gemów

x_change = 40
y_change = 40

black = (0,0,0)
white = (255,255,255)
red = (255,0,0)

gameDisplay = pygame.display.set_mode((WIDTH,HEIGHT))
pygame.display.set_caption("Game")
clock = pygame.time.Clock()

carImg = pygame.image.load('CandySaga/cursor.png')
carImg = pygame.transform.scale(carImg, (40, 40))

GreenGem = pygame.image.load('CandySaga/GreenGem.png')
GreenGem = pygame.transform.scale(GreenGem, (40, 40))

RedGem = pygame.image.load('CandySaga/RedGem.png')
RedGem = pygame.transform.scale(RedGem, (40, 40))

YellowGem = pygame.image.load('CandySaga/YellowGem.png')
YellowGem = pygame.transform.scale(YellowGem, (40, 40))

BlueGem = pygame.image.load('CandySaga/BlueGem.png')
BlueGem = pygame.transform.scale(BlueGem, (40, 40))


gems = []
for y in range(1,13):
    for x in range(1,13):
        gems.append("gem" + str(x) + "_" + str(y))

gPion = []
for i in range(12):
    for j in range(i,144,12):
        gPion.append(j)

points = 0

class Gem:
    def __init__(self,color,img,x,y):
        self.color = color
        self.img = img
        self.x = x 
        self.y = y

def delay():
    global points
    pygame.time.delay(100)
    gameDisplay.fill(black)
    drawGems()
    score(points)
    pygame.display.update()

def score(points):
    font = pygame.font.SysFont(None, 40)
    text = font.render("Score: " + str(points), True, white)
    gameDisplay.blit(text,((WIDTH/2-50),80))
    pygame.display.update()

def randomizeGems():
    rand = random.randint(0,3)
    if rand == 0:
        color = 'g'
        img = GreenGem
    elif rand == 1:
        color = 'r'
        img = RedGem
    elif rand == 2:
        color = 'y'
        img = YellowGem 
    elif rand == 3:
        color = 'b'
        img = BlueGem
    return color,img

def fixGems():
    fix = True
    while fix:
        fix = False

        #poziomo
        for i in range(2,144):
            fixCon = True
            while fixCon:
                if gems[i].color == gems[i-1].color and gems[i].color == gems[i-2].color:
                    fix = True
                    gems[i].color, gems[i].img = randomizeGems()
                    gems[i-1].color, gems[i-1].img = randomizeGems()
                else:
                    fixCon = False
                    
        #pionowo
        for i in range(2,len(gPion)):
            fixCon = True
            while fixCon:
                if gems[gPion[i]].color == gems[gPion[i-1]].color and gems[gPion[i]].color == gems[gPion[i-2]].color:
                    fix = True
                    gems[gPion[i]].color, gems[gPion[i]].img = randomizeGems()
                    gems[gPion[i-1]].color, gems[gPion[i-1]].img = randomizeGems()
                else:
                    fixCon = False

def generateGems():
    i = 0
    for y in range(120,HEIGHT,40):
        for x in range(0,WIDTH,40):
            color, img = randomizeGems()
            gems[i] = Gem(color,img,x,y)
            i += 1
    fixGems()

def drawGems():
    for i in range(144):
        gameDisplay.blit(gems[i].img,(gems[i].x,gems[i].y))

def chosingText():
    font = pygame.font.SysFont(None, 25)
    text = font.render("^", True, white)
    gameDisplay.blit(text,(WIDTH/2-4,20))
    text = font.render("<--v-->", True, white)
    gameDisplay.blit(text,((WIDTH/2)-25,30))
    pygame.display.update()

def chosing(Cord):
    chosingText()
    pygame.event.clear()
    while True:
        event = pygame.event.wait()
        if event.type == pygame.QUIT:
            pygame.quit()
            sys.exit()
        if event.type == pygame.KEYDOWN:
            if event.key == pygame.K_RETURN:
                break
            if event.key == pygame.K_LEFT:
                if Cord % 12 > 0:
                    gems[Cord].color,gems[Cord-1].color =  gems[Cord-1].color,gems[Cord].color
                    gems[Cord].img,gems[Cord-1].img =  gems[Cord-1].img,gems[Cord].img
                break
            if event.key == pygame.K_RIGHT:
                if Cord % 12 < 11:
                    gems[Cord].color,gems[Cord+1].color =  gems[Cord+1].color,gems[Cord].color
                    gems[Cord].img,gems[Cord+1].img =  gems[Cord+1].img,gems[Cord].img
                break
            if event.key == pygame.K_UP:
                if Cord > 11:
                    gems[Cord].color,gems[Cord-12].color =  gems[Cord-12].color,gems[Cord].color
                    gems[Cord].img,gems[Cord-12].img =  gems[Cord-12].img,gems[Cord].img
                break
            if event.key == pygame.K_DOWN:
                if Cord < 132:
                    gems[Cord].color,gems[Cord+12].color =  gems[Cord+12].color,gems[Cord].color
                    gems[Cord].img,gems[Cord+12].img =  gems[Cord+12].img,gems[Cord].img
                break

def fillGems():
    
    isBlank = True
    while isBlank:
        isBlank = False
        for i in range(143,11,-1):
            if gems[i].color == 'null' and gems[i-12].color != 'null':
                isBlank = True
                gems[i].color,gems[i-12].color =  gems[i-12].color,gems[i].color
                gems[i].img,gems[i-12].img =  gems[i-12].img,gems[i].img
                delay()

        for i in range(11,-1,-1):
            if gems[i].color == 'null':
                isBlank = True
                color, img = randomizeGems()
                gems[i].color = color
                gems[i].img = img
                delay()

def checkGems():
    global points 
    #poziomo
    matchGems = []
    for y in range(12):
        for x in range(2,12):
            cord = y*12 + x
            if gems[cord].color == gems[cord-1].color and gems[cord].color == gems[cord-2].color:
                points += 100
                matchGems.append(cord)
                matchGems.append(cord-1)
                matchGems.append(cord-2)
                
    for y in range(2,12):
        for x in range(12):
            cord = y*12 + x
            if gems[cord].color == gems[cord-12].color and gems[cord].color == gems[cord-24].color:
                points += 100
                matchGems.append(cord)
                matchGems.append(cord-12)
                matchGems.append(cord-24)

    for match in matchGems:
        gems[match].img = carImg
        gems[match].color = 'null'

    if len(matchGems) > 0:
        print("XD")
        fillGems()
        
def car(x,y):
    gameDisplay.blit(carImg,(x,y))

def game_loop():
    global points

    x = 200
    y = 280
    x_cursor = 5
    y_cursor = 4

    while True:

        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                quit()
            if event.type == pygame.KEYDOWN:
                if event.key == pygame.K_LEFT:
                    x += -x_change
                    if x_cursor > 0:
                        x_cursor -= 1
                if event.key == pygame.K_RIGHT:
                    x +=  x_change
                    if x_cursor < 11:
                        x_cursor += 1
                if event.key == pygame.K_UP:
                    y += -y_change
                    if y_cursor > 0:
                        y_cursor -= 1
                if event.key == pygame.K_DOWN:
                    y += y_change
                    if y_cursor < 11:
                        y_cursor += 1
                if event.key == pygame.K_RETURN: # enter
                    chosing(y_cursor*12+x_cursor)
                if event.key == pygame.K_r:
                    main()               

        checkGems()
        if x > WIDTH - 40:
            x = WIDTH - 40
        if x < 0:
            x = 0
        if y > HEIGHT - 40:
            y = HEIGHT - 40
        if y < 120:
            y = 120
        
        gameDisplay.fill(black)
        car(x,y)
        drawGems()
        score(points)
        pygame.display.update()
        clock.tick(15)
        
def main():
    generateGems()
    game_loop()

main()

pygame.quit()
quit()