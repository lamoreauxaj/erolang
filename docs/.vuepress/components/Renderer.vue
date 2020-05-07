<template>
    <div class="renderer">
        <div class="canvas" ref="canvas">

        </div>
    </div>
</template>

<script>
import * as THREE from 'three/build/three.module.js'

export default {
    name: 'renderer',
    props: {
        objects: {
            required: true,
            type: Array
        }
    },
    data() {
        return {
            error: '',
            mesh: undefined,
            camera: undefined,
            scene: undefined,
            renderer: undefined
        }
    },
    computed: {
    },
    mounted() {

        this.camera = new THREE.PerspectiveCamera( 70, window.innerWidth / window.innerHeight, 0.01, 10 );
        this.camera.position.z = 1;
    
        this.scene = new THREE.Scene();

        // v-for loop through all the items in object? idk syntax
        for (item in objects) {
            if (item.figure == "sphere") {
                // template
                var geometry = new THREE.SphereGeometry( 5, 32, 32 );
                var material = new THREE.MeshBasicMaterial( {color: 0xffff00} );
                var sphere = new THREE.Mesh( geometry, material );
                this.scene.add( sphere );
            } else if (item.figure == "circle") {
                // template
                var geometry = new THREE.CircleGeometry( 5, 32 );
                var material = new THREE.MeshBasicMaterial( { color: 0xffff00 } );
                var circle = new THREE.Mesh( geometry, material );
                this.scene.add( circle );
            } else if (item.figure == "plane") {
                // template
                var geometry = new THREE.PlaneGeometry( 5, 20, 32 );
                var material = new THREE.MeshBasicMaterial( {color: 0xffff00, side: THREE.DoubleSide} );
                var plane = new THREE.Mesh( geometry, material );
                this.scene.add( plane );
            } else if (item.figure == "line") {

            } else if (item.figure == "point") {

            }
        }
    
        // let geometry = new THREE.BoxGeometry( 0.2, 0.2, 0.2 );
        // let material = new THREE.MeshNormalMaterial();
    
        // this.mesh = new THREE.Mesh( geometry, material );
        // this.scene.add( this.mesh );
    
        this.renderer = new THREE.WebGLRenderer( { antialias: true } );
        this.renderer.setSize(640, 640)
        renderer.setSize( window.innerWidth, window.innerHeight );
        this.$refs.canvas.appendChild( this.renderer.domElement );
    
        this.animate()
    },
    methods: {
        animate() {
            requestAnimationFrame( this.animate );
            this.mesh.rotation.x += 0.01;
            this.mesh.rotation.y += 0.02;
            this.renderer.render( this.scene, this.camera );
        }
    }
}
</script>

<style scoped>
.renderer {
    display: flex;
    flex-direction: column;
    align-items: center;
}
.renderer-canvas {
    background-color: #ddd;
}
</style>