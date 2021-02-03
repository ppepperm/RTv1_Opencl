#include "../includes/cl_header.h"

/*t_object *generate_objects()
{
    t_object *object = (t_object*)malloc(sizeof (t_object));
    object->head = object;
    object->next = null;
    object->pos = init_p3(0, 0, 20);
    object->t = init_transform(init_p3(1, 0, 0),
                               init_p3(0, 1, 0),
                               init_p3(0, 0, 1));
    object->i_t = i_transform(object->t);
    object->reflect = 20;
    object->colour = init_rgb(255,100,0,255);

    t_sphere *tmp = (t_sphere*)malloc(sizeof(t_sphere));
    tmp->pos = init_p3(0, 0, 20);
    tmp->r = 6;

    object->data = (void*)tmp;
    object->type = T_SPHERE;
}

t_light *generate_light()
{
    t_light *light = (t_light*)malloc(sizeof (t_light));
    light->type = L_DOT;
    light->i = 1;
    light->next = null;
    light->data = init_p3(0, 0, -20);

    return light;
}

void init_scene(t_scene *scene)
{
    scene->objects = generate_objects();
    scene->lights = generane_light();
    scene->camera = init_camera(init_p3(0, 0, 0),
                                init_p3(1, 0, 0),
                                init_p3(0, 1, 0),
                                init_p3(0, 0, 1));
    scene->chosen = null;
}*/

__kernel void vector_add(__global unsigned char *buffer)
{
// Get the index of the current element to be processed
	int coll = get_global_id(0);
	int row = 0;
	int pitch = (int)(W_W* sizeof(unsigned int));

	while (row < W_H)
	{
		buffer[coll * 4 + 0 + row * pitch] = 255;
		buffer[coll * 4 + 1 + row * pitch] = 200;
		buffer[coll * 4 + 2 + row * pitch] = 255;
		buffer[coll * 4 + 3 + row * pitch] = 0;
		row++;
	}


}
