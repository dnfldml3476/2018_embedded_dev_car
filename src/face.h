#ifndef __FACE_H_
#define __FACE_H_

#include <Python.h>
#include <stdio.h>

/* declare python objects */
PyObject *PyModule;
PyObject *PyImport;

void load_image(char *filename);
void face_encodings(char *filename);
int face_compare(char *filename);

#endif
