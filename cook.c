/*
** EPITECH PROJECT, 2017
** my_cook
** File description:
** my_cook
*/

#include <SFML/Graphics/Color.h>
#include <SFML/Graphics/RenderWindow.h>
#include <SFML/Graphics/Types.h>
#include <SFML/Audio/Types.h>
#include <SFML/Audio/SoundStatus.h>
#include <SFML/Audio.h>
#include <SFML/Graphics.h>
#include <SFML/Window/Export.h>
#include "main.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <stdio.h>

void close_window(wido_t *window)
{
	while (sfRenderWindow_pollEvent(window->window, &window->event)) {
		if (window->event.type == sfEvtClosed)
			sfRenderWindow_close(window->window);
	}
}

void reset_particule(rain_t *rain, int i, game_t game)
{
	float angle;
	float speed;
	sfVector2f posi;
	sfVertex *vertex;
	sfColor color;

	vertex = sfVertexArray_getVertex(rain->vertices, i);

	if (rand() % 2 == 0)
		rain->parti[i].timelife = \
sfMilliseconds((rand() % game.timelife) + game.morelife);
	angle = ((rand() % 360) * M_PI) / 180;
	speed = (rand() % 500) + 50;
	posi.y = sin(angle) * speed;
	posi.x = cos(angle) * speed;
	rain->parti[i].posi = posi;
	vertex->position.y = rain->emitter.y;
	vertex->position.x = rain->emitter.x;
	color.r = game.red;
	color.g = game.green;
	color.b = game.bleu;
	color.a = game.trans;
	vertex->color = color;
}

void update_particule(rain_t *rain, sfTime time, game_t game)
{
	sfVertex *vertex;

	for (int i = 0; i < rain->nbr; i++) {
		rain->parti[i].timelife.microseconds -= time.microseconds;
		if (rain->parti[i].timelife.microseconds <= 0)
			reset_particule(rain, i, game);
		vertex = sfVertexArray_getVertex(rain->vertices, i);
		vertex->position.y += (rain->parti[i].posi.y * sfTime_asSeconds(time)) * game.speed;
		vertex->position.x += (rain->parti[i].posi.x * sfTime_asSeconds(time)) * game.speed;
	}
}

void display_sprite(wido_t *window, rain_t *rain)
{
	sfRenderWindow_clear(window->window, sfBlack);
	sfRenderWindow_drawVertexArray(window->window, rain->vertices, NULL);
	sfRenderWindow_display(window->window);
}

void all_game(wido_t *window, sfClock *clock, rain_t *rain, game_t game)
{
	sfTime time;
	sfVector2i mouse;

	close_window(window);
	mouse = sfMouse_getPositionRenderWindow(window->window);
	rain->emitter.x = (float)mouse.x;
	rain->emitter.y = (float)mouse.y;
	time = sfClock_restart(clock);
	update_particule(rain, time, game);
	display_sprite(window, rain);
}

int open_window(wido_t *window)
{
	sfVideoMode mode = {HT, WT, 32};

	window->window = sfRenderWindow_create(mode, "particule", sfResize | sfClose, NULL);
	return (0);
}

void cook(wido_t *window, rain_t rain, game_t game)
{
	sfClock *clock = sfClock_create();

	open_window(window);
	while (sfRenderWindow_isOpen(window->window))
		all_game(window, clock, &rain, game);
}

sfPrimitiveType get_type_particule(void)
{
	char *name = NULL;
	size_t n = 0;

	printf("Triangles = T   Points = P  Lines = L\n");
	getline(&name, &n, stdin);
	if (name == NULL)
		return (sfPoints);
	if (strcmp(name, "T\n") == 0)
		return (sfTriangles);
	else if (strcmp(name, "L\n") == 0)
		return (sfLines);
	else
		return (sfPoints);
}

int get_nbr_particule(void)
{
	char *name = NULL;
	size_t n = 0;
	int nbr = 0;
	int i = 0;

	printf("Nbr particule = ");
	getline(&name, &n, stdin);
	if (name == NULL || name[0] == '\0')
		return (100);
	for (; name[i] != '\n' && name[i] != '\0'; i++);
	name[i] = '\0';
	nbr = atoi(name);
	return (nbr);
}

int get_lifetime(void)
{
	char *name = NULL;
	size_t n = 0;
	int nbr = 0;
	int i = 0;

	printf("Lifetime = ");
	getline(&name, &n, stdin);
	if (name == NULL || name[0] == '\0')
		return (100);
	for (; name[i] != '\n' && name[i] != '\0'; i++);
	name[i] = '\0';
	nbr = atoi(name);
	return (nbr);
}

int get_lifetime_more(void)
{
	char *name = NULL;
	size_t n = 0;
	int nbr = 0;
	int i = 0;

	printf("Lifetime more = ");
	getline(&name, &n, stdin);
	if (name == NULL || name[0] == '\0')
		return (0);
	for (; name[i] != '\n' && name[i] != '\0'; i++);
	name[i] = '\0';
	nbr = atoi(name);
	return (nbr);
}

void get_color(game_t *game)
{
	char *name = NULL;
	size_t n = 0;
	int i = 0;

	printf("Color red = ");
	getline(&name, &n, stdin);
	for (; name[i] != '\n' && name[i] != '\0'; i++);
	name[i] = '\0';
	game->red = atoi(name);
	i = 0;
	printf("Color green = ");
	getline(&name, &n, stdin);
	for (; name[i] != '\n' && name[i] != '\0'; i++);
	name[i] = '\0';
	game->green = atoi(name);
	i = 0;
	printf("Color blue = ");
	getline(&name, &n, stdin);
	for (; name[i] != '\n' && name[i] != '\0'; i++);
	name[i] = '\0';
	game->bleu = atoi(name);
	i = 0;
	printf("Color light = ");
	getline(&name, &n, stdin);
	for (; name[i] != '\n' && name[i] != '\0'; i++);
	name[i] = '\0';
	game->trans = atoi(name);
}

int get_speed_particule(void)
{
	char *name = NULL;
	size_t n = 0;
	int nbr = 0;
	int i = 0;

	printf("Speed particule = ");
	getline(&name, &n, stdin);
	if (name == NULL || name[0] == '\0')
		return (0);
	for (; name[i] != '\n' && name[i] != '\0'; i++);
	name[i] = '\0';
	nbr = atoi(name);
	return (nbr);
}

int main(int ac, char **av)
{
	wido_t *window = malloc(sizeof(*window));
	game_t game;
	rain_t rain;
	sfVector2f posi = {100, 100};

	rain.vertices = sfVertexArray_create();
	game.type = get_type_particule();
	rain.nbr = get_nbr_particule();
	game.timelife = get_lifetime();
	game.morelife = get_lifetime_more();
	game.speed = get_speed_particule();
	get_color(&game);
	sfVertexArray_resize(rain.vertices, rain.nbr);
	sfVertexArray_setPrimitiveType(rain.vertices, game.type);
	rain.parti = malloc(sizeof(partitule_t) * rain.nbr);
	for (int i = 0; i < rain.nbr; i++) {
		rain.parti[i].timelife = sfSeconds(0);
		rain.parti[i].posi = posi;
	}
	cook(window, rain, game);
	free(window);
	return (0);
}
