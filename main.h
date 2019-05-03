/*
** EPITECH PROJECT, 2017
** my_hunter
** File description:
** my_hunter
*/

#include <SFML/Graphics.h>
#include <SFML/Audio.h>
#include <SFML/System/Export.h>
#include <SFML/System/Time.h>
#include <SFML/System/Types.h>

#define HT 1200
#define WT 800

#ifndef _MAIN_H_
#define _MAIN_H_

struct game_s {
	sfPrimitiveType type;
	int timelife;
	int morelife;
	int red;
	int trans;
	int green;
	int bleu;
	int speed;
};
typedef struct game_s game_t;

struct partitule_s {
	sfTime timelife;
	sfVector2f posi;
};
typedef struct partitule_s partitule_t;

struct rain_s {
	partitule_t *parti;
	int nbr;
	sfVertexArray *vertices;
	sfVector2f emitter;
};
typedef struct rain_s rain_t;

struct window {
	sfRenderWindow *window;
	sfEvent event;
};
typedef struct window wido_t;

#endif