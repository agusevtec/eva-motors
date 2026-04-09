

# Class evam::RingBuffer

**template &lt;typename T, unsigned char N&gt;**



[**ClassList**](annotated.md) **>** [**evam**](namespaceevam.md) **>** [**RingBuffer**](classevam_1_1_ring_buffer.md)










































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**RingBuffer**](#function-ringbuffer) () <br> |
|  T | [**get**](#function-get) (unsigned char index) const<br> |
|  bool | [**isFull**](#function-isfull) () const<br> |
|  void | [**put**](#function-put) (const T & value) <br> |
|  unsigned char | [**size**](#function-size) () const<br> |




























## Public Functions Documentation




### function RingBuffer 

```C++
inline evam::RingBuffer::RingBuffer () 
```




<hr>



### function get 

```C++
inline T evam::RingBuffer::get (
    unsigned char index
) const
```




<hr>



### function isFull 

```C++
inline bool evam::RingBuffer::isFull () const
```




<hr>



### function put 

```C++
inline void evam::RingBuffer::put (
    const T & value
) 
```




<hr>



### function size 

```C++
inline unsigned char evam::RingBuffer::size () const
```




<hr>

------------------------------
The documentation for this class was generated from the following file `src/evamRingBuffer.h`

