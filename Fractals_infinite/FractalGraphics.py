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

        self._initAssets()

    def _initAssets(self):
        self.back = pygame.image.load('./images/back.png')
        self.back = pygame.transform.scale(self.back, (int(self.back.get_width() / 11), int(self.back.get_height() / 11)))

        self.upArrow = pygame.image.load('./images/arrow.png')
        self.upArrow = pygame.transform.rotate(self.upArrow, 90)
        self.upArrow = pygame.transform.scale(self.upArrow, (int(self.upArrow.get_width() / 7), int(self.upArrow.get_height() / 7)))

        self.rightArrow = pygame.image.load('./images/arrow.png')
        self.rightArrow = pygame.transform.scale(self.rightArrow, (int(self.rightArrow.get_width() / 7), int(self.rightArrow.get_height() / 7)))

        self.downArrow = pygame.image.load('./images/arrow.png')
        self.downArrow = pygame.transform.rotate(self.downArrow, 270)
        self.downArrow = pygame.transform.scale(self.downArrow, (int(self.downArrow.get_width() / 7), int(self.downArrow.get_height() / 7)))

        self.leftArrow = pygame.image.load('./images/arrow.png')
        self.leftArrow = pygame.transform.rotate(self.leftArrow, 180)
        self.leftArrow = pygame.transform.scale(self.leftArrow, (int(self.leftArrow.get_width() / 7), int(self.leftArrow.get_height() / 7)))

        self.plus = pygame.image.load('./images/plus.png')
        self.plus = pygame.transform.scale(self.plus, (int(self.plus.get_width() / 7), int(self.plus.get_height() / 7)))

        self.minus = pygame.image.load('./images/minus.png')
        self.minus = pygame.transform.scale(self.minus, (int(self.minus.get_width() / 7), int(self.minus.get_height() / 7)))

        self.zoomFont = pygame.font.SysFont('Comic Sans MS', 80)

    def play(self):
        while True:
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    sys.exit()

                if event.type == pygame.MOUSEBUTTONDOWN and event.button == 1:
                    rect = self.back.get_rect().move((15, 20))

                    if rect.collidepoint(event.pos):                        
                        return

                    rect = self.upArrow.get_rect().move((int(self.upArrow.get_width()), int(self.screen.get_height() - 3 * self.upArrow.get_height())))

                    if rect.collidepoint(event.pos):                        
                        self.fractal.move(pygame.K_UP)

                    rect = self.rightArrow.get_rect().move((int(self.rightArrow.get_width() * 2), int(self.screen.get_height() - 2 * self.rightArrow.get_height())))

                    if rect.collidepoint(event.pos):                        
                        self.fractal.move(pygame.K_RIGHT)

                    rect = self.downArrow.get_rect().move((int(self.downArrow.get_width()), int(self.screen.get_height() - self.downArrow.get_height())))

                    if rect.collidepoint(event.pos):                        
                        self.fractal.move(pygame.K_DOWN)

                    rect = self.leftArrow.get_rect().move((0, int(self.screen.get_height() - 2 * self.leftArrow.get_height())))

                    if rect.collidepoint(event.pos):                        
                        self.fractal.move(pygame.K_LEFT)

                    rect = self.plus.get_rect().move((int(self.screen.get_width() - 1.3 * self.plus.get_width()), int(self.screen.get_height() - 2 * self.plus.get_height())))

                    if rect.collidepoint(event.pos):                        
                        self.fractal.zoomIn((0.5, 0.5))

                    rect = self.minus.get_rect().move((int(self.screen.get_width() - 1.3 * self.minus.get_width()), int(self.screen.get_height() - 2 * self.minus.get_height())))

                    if rect.collidepoint(event.pos):                        
                        self.fractal.zoomOut()

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

        self.screen.blit(self.back, (15, 20))

        self.screen.blit(self.upArrow, (int(self.upArrow.get_width()), int(self.screen.get_height() - 3 * self.upArrow.get_height())))
        self.screen.blit(self.rightArrow, (int(self.rightArrow.get_width() * 2), int(self.screen.get_height() - 2 * self.rightArrow.get_height())))
        self.screen.blit(self.downArrow, (int(self.downArrow.get_width()), int(self.screen.get_height() - self.downArrow.get_height())))
        self.screen.blit(self.leftArrow, (0, int(self.screen.get_height() - 2 * self.leftArrow.get_height())))

        self.screen.blit(self.plus, (int(self.screen.get_width() - 1.3 * self.plus.get_width()), int(self.screen.get_height() - 2 * self.plus.get_height())))
        self.screen.blit(self.minus, (int(self.screen.get_width() - 1.3 * self.minus.get_width()), int(self.screen.get_height() - 2 * self.minus.get_height())))

        zoom = str(int(self.fractal.getZoom()))
        self.screen.blit(self.zoomFont.render(zoom, False, (255, 255, 255)), (int(self.screen.get_width() - 145 - len(zoom) * 30), 50))
        
        pygame.display.flip()
