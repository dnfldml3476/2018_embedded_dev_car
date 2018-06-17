#ifndef __FACE_H_
#define __FACE_H_

#include <stdio.h>
#include <Python.h>
#include <camera.h>

/* declare python objects */
PyObject *PyModule;
PyObject *PyArg1, *PyArg2;
PyObject *PyLoad_image, *PyFace_encodings, *PyCompare_faces;
PyObject *PyUser, *PyPicture;
PyObject *PyEnc1, *PyEnc2;
PyObject *first_enc1, *first_enc2;
PyObject *ret;


void face_init();
void load_image(char *filename, int check);
void face_encodings(PyObject *image, int check);
int face_compare(double tolerance); 

#endif
