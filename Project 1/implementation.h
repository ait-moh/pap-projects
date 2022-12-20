//DON'T MODIFY THIS FUNCTION
void naive(int *src, int *dst, int SIZE){
    for(int i=0; i < SIZE; i++){
        for(int j=0; j < SIZE; j++){
            dst[(j * SIZE) + i] = src[(i * SIZE) + j];
        }
    } 
}
    
//DON'T MODIFY THE HEADER OF THE FUNCTION
void aware(int *src, int *dst, int SIZE)
{ 
    // the key word: "register" makes the variable accessible from a temporary cache rather than
    // to be created in the main memory and that improves the runtime .
    int register block_size = 64;

    for (register int i = 0; i < SIZE; i += block_size) {


    for (register int j = 0; j < SIZE; j += block_size) {

        // transposing the block with the two inner loops
        for (register int k = i; k < i + block_size; ++k) {


            for (register int l = j; l < j + block_size; ++l) {

                dst[k + l*SIZE] = src[l + k*SIZE];
            }

        }
    }
}
  
}



// those three functions were copied from the internet to draw the z curve
// source : https://fgiesen.wordpress.com/2009/12/13/decoding-morton-codes/
int Compact1By1(int x)
{   
  x &= 0x55555555;              // x = -f-e -d-c -b-a -9-8 -7-6 -5-4 -3-2 -1-0

  x = (x ^ (x >>  1)) & 0x33333333; // x = --fe --dc --ba --98 --76 --54 --32 --10

  x = (x ^ (x >>  2)) & 0x0f0f0f0f; // x = ---- fedc ---- ba98 ---- 7654 ---- 3210

  x = (x ^ (x >>  4)) & 0x00ff00ff; // x = ---- ---- fedc ba98 ---- ---- 7654 3210

  x = (x ^ (x >>  8)) & 0x0000ffff; // x = ---- ---- ---- ---- fedc ba98 7654 3210

  return x;
}

int DecodeMorton2X(int code)
{
  return Compact1By1(code >> 0);
}

int DecodeMorton2Y(int code)
{
  return Compact1By1(code >> 1);
}

//DON'T MODIFY THE HEADER OF THE FUNCTION
void oblivious(int *src, int *dst, int SIZE)
{
   register int x=0;
   register int y=0;

    for(register int z=0; z < SIZE*SIZE; z++){
    // x and y are drawing the z curve
    x=Compact1By1(z >> 0);
    y=Compact1By1(z >> 1);
     
     // apply the transposition normally
     dst[(y * SIZE) + x] = src[(x * SIZE) + y];

    }
  
}

//DON'T MODIFY THE HEADER OF THE FUNCTION
void optimized(int *src, int *dst, int SIZE)
{
// this function is mixing the aware and the oblivious methods    
int register block_size = 8;
int register x = 0;
int register y = 0;



   for (register int z = 0; z < SIZE*SIZE; z += block_size*block_size) {
    // x and y are drawing the z curve
    x=Compact1By1(z >> 0);
    y=Compact1By1(z >> 1);

        // transposing the block with the two inner loops
        for (register int i = x; i < x + block_size; ++i) {

            for (register int j = y; j < y + block_size; ++j) {


                dst[i + j*SIZE] = src[j + i*SIZE];
            }
  
        }
}


}

    //printf("\noptimized version not implemented...\n"); 