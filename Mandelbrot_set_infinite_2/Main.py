from MainMenuGraphics import MainMenuGraphics
import pygame

pygame.init()
pygame.display.set_caption('Mandelbrot/Julia set')

menu = MainMenuGraphics()
menu.play()