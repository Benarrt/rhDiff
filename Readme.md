Simple implementation of rolling hash file diffing algorithm

## Usage

```
cmake -S. -Bbuild
cd build
cmake --build .
ctest
```

### chunk_test

Tests if chunks are correctly hashed and if no collision occures

### signature_test

Tests if signature for base_file is created correctly.


### delta_test

Tests id delta for signatutre_file and new_file is created correctly.
**Not yet implemented.**