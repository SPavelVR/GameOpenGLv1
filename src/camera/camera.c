
#include <stdlib.h>

#include "camera/camera.h"
#include "window/window.h"


static void print_matr4(Matrix4 mat) {
    printf("IN CAMERA: \n");
    for (char i = 0; i < 4; i++)
    {
        for (char j = 0; j < 4; j++)
        {
            printf("%f ", mat[i][j]);
        }
        printf("\n");
    }
}

static unsigned int id_camera = 0;


Camera* init_camera(Vector3 position, float fov, float sr_x, float sr_y, float sr_z) {
    Camera* camera = calloc(1, sizeof(Camera));

    if (camera == NULL) return NULL;

    copyVector3(camera->position, position);
    camera->fov = fov;
    setEMatrix4(camera->rotation, 1.0f);
    camera_update_vectors(camera);
    camera_rotate(camera, sr_x, sr_y, sr_z);
    id_camera++;
    camera->id = id_camera;
    return camera;
};

void free_camera(Camera* camera) {
    if (camera == NULL) return  ;

    free(camera);
};

void camera_update_vectors(Camera* camera) {
    Vector4 temp;

    setVector4(temp, 0, 0, -1);
    vm3_mul(camera->front, camera->rotation, temp);

    setVector4(temp, 1, 0, 0);
    vm3_mul(camera->right, camera->rotation, temp);

    setVector4(temp, 0, 1, 0);
    vm3_mul(camera->up, camera->rotation, temp);
};

void camera_rotate(Camera* camera, float x, float y, float z) {

    camera->rotate_x += x;
    camera->rotate_y += y;
    camera->rotate_z += z;

    setEMatrix4(camera->rotation, 1.0f);

    mat4_mul_rotade_r(camera->rotation, camera->rotate_z, 2);
    mat4_mul_rotade_r(camera->rotation, camera->rotate_y, 1);
    mat4_mul_rotade_r(camera->rotation, camera->rotate_x, 0);

    camera_update_vectors(camera);
};

float* camera_get_position(Camera* camera) {
    if (camera == NULL) return NULL;
    return (float*) camera->position;
};

void camera_set_projection(Camera* camera, Matrix4 mat) {
    int w, h;
    window_get_size(&w, &h);
    
    float aspect = ((float) w) / ((float) h);

    //mat4_ortho(mat, (float) w, (float) h, 100.0f);
    mat4_perspectiv(mat, camera->fov, aspect, 0.1f, 100.0f);
};

void camera_set_view(Camera* camera, Matrix4 mat) {
    Vector3 pl = {
       camera->position[0] + camera->front[0],
        camera->position[1] + camera->front[1],
        camera->position[2] + camera->front[2]
    };

    mat4_look_at(mat, camera->position, pl, camera->up);
};

void camera_set_projview(Camera* camera, Matrix4 out) {
    setMatrix4(out, 0.0f);

    Matrix4 proj, view;

    camera_set_projection(camera, proj);
    camera_set_view(camera, view);
    mat4_mul(out, proj, view);
};

float* camera_get_front(Camera* camera) 
{
    if (camera == NULL) return NULL;

    return (float*) camera->front;
}

float* camera_get_right(Camera* camera)
{
    if (camera == NULL) return NULL;

    return (float*) camera->right;
};
float* camera_get_up(Camera* camera)
{
    if (camera == NULL) return NULL;

    return (float*) camera->up;
};