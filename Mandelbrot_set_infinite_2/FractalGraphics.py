from Fractal import Fractal
import sys
import pygame

class FractalGraphics:
    def __init__(self, screen, underlyingFractal):
        self.screen = screen

        self.renderSize = (720, 510)
        self.renderScreen = pygame.Surface(self.renderSize)

        self.fractal = Fractal(self.renderScreen.get_rect().size, underlyingFractal)
        self.fractal.draw()

    def play(self):
        while True:
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    sys.exit()

                if event.type == pygame.KEYDOWN:
                    if event.key == pygame.K_ESCAPE:
                        return

                    if event.key == pygame.K_EQUALS:
                        x, y = pygame.mouse.get_pos()

                        x /= self.screen.get_rect().size[0]
                        y /= self.screen.get_rect().size[1]

                        self.fractal.zoomIn((x, y))
                    if event.key == pygame.K_MINUS:
                        self.fractal.zoomOut()

                    if event.key == pygame.K_UP or \
                            event.key == pygame.K_RIGHT or \
                            event.key == pygame.K_DOWN or \
                            event.key == pygame.K_LEFT:
                        self.fractal.move(event.key)
            self.show()

    def show(self):        
        self.renderScreen.blit(self.fractal.getFractal(), (0, 0))

        self.screen.blit(pygame.transform.scale(self.renderScreen, self.screen.get_rect().size), (0, 0))
        pygame.display.flip()
