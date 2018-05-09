# CaesarCipher


## Description:

> This is a basic Caesar Cipher program that will perform a Caesar shift on a plaintext file specified by an input shify value.


###### Requirements:
  * gcc
  * A plaintext file you want to encrypt

---

### Compile using GCC:


```bash
gcc -o cipher cipher.c
```
---

### How to Run:


To run encryption:

```bash
./cipher -E $FILE -s 3
```

> This will encrypt $FILE using a shift of 3.


To run decryption:

```bash
 ./cipher -D $FILE -s 3
```

> This will decrypt $FILE using a shift of 3.
