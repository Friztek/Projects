 def fillGems():
    isBlank = True
    while isBlank:
        isBlank = False
        for y in range(11,0,-1):
            for x in range(11,-1,-1):
                i = y*12 + x
                if gems[i].color == 'null' and gems[i-12].color != 'null':
                    isBlank = True
                    gems[i].color,gems[i-12].color =  gems[i-12].color,gems[i].color
                    gems[i].img,gems[i-12].img =  gems[i-12].img,gems[i].img
                if isBlank == True:
                    pygame.time.delay(30)
                    gameDisplay.fill(black)
                    drawGems()
                    pygame.display.update()