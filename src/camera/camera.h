
#ifndef __CAMERA_H
#define __CAMERA_H 1

#include <matrix4.h>

typedef struct Camera {

    Vector4 front;
    Vector4 up;
    Vector4 right;
    Vector4 position;
    Matrix4 rotation;
    float fov;
    unsigned int id;

} Camera;

Camera* init_camera(Vector4 position, float fov);
void free_camera(Camera* camera);

void camera_update_vectors(Camera* camera);
void camera_rotate(Camera* camera, float x, float y, float z);

void camera_set_projection(Camera* camera, Matrix4 mat);
void camera_set_view(Camera* camera, Matrix4 mat);
void camera_set_projview(Camera* camera, Matrix4 out);

float* camera_get_position(Camera* camera);

#endif