# Multiple Passes Rendering branch

##### Deferred rendering development from XDzZyq



### Features

 - [x] multi-passes buffering
 - [x] Multi-passes processing
	- [x] FXAA
	- [x] SSAO
	- [x] Simple Convolution
 - [x] Multi-passes composition
	- [ ] PBR deferred rendering
		- [ ] PBR direct Lighting
			- [x] Point light
			- [x] Sun light [@theta-lin](https://github.com/theta-lin)
			- [x] Spot light [@theta-lin](https://github.com/theta-lin)
			- [x] Area light (currently only support pure color convex polygon) [@theta-lin](https://github.com/theta-lin)

			- [ ] Shadow Map
		- [x] PBR IBL

- [x] advanced StorageBuffer
- [ ] advanced Texture storage
	- [ ] Cube map <-> Equirectangular map

 - [ ] editing elements
	- [x] outline

 - [x] Post Processing
	- [ ] Processing Chain
	- [ ] Fragment Shader <-> Compute Shader

### UI
 - [ ] Post Processing Flow editor
	- [ ] Node editing
	- [ ] Shader editing

### Advanced

 - [x] Dynamic passes binding
 - [ ] Dynamic shader value<->texture altering
