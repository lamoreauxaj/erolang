<template>
    <div class="renderer">
        <div class="renderer-canvas" ref="canvas">
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
        console.log(window.innerWidth / window.innerHeight)
        this.camera = new THREE.PerspectiveCamera( 70, 1, 0.01, 10 )
        this.camera.position.z = 10
    
        this.scene = new THREE.Scene()
        for (let item of this.objects) {
            if (item.figure == "sphere") {
                // template
                const geometry = new THREE.SphereGeometry( 5, 32, 32 )
                const material = new THREE.MeshBasicMaterial( {color: 0x000000} )
                const sphere = new THREE.Mesh( geometry, material )
                this.scene.add( sphere )
            } else if (item.figure == "circle") {
                // template
                const geometry = new THREE.CircleGeometry( item.radius, 64 )
                const material = new THREE.LineBasicMaterial( { color: 0x000000 } )
                geometry.vertices.shift()
                const circle = new THREE.LineLoop( geometry, material )
                circle.position.set(...item.center)
                circle.lookAt(new THREE.Vector3(...item.norm))
                this.scene.add( circle )
            } else if (item.figure == "plane") {
                // template
                const geometry = new THREE.PlaneGeometry(1000, 1000, 32, 32)
                const material = new THREE.MeshPhongMaterial({color: 0x000000, side: THREE.DoubleSide, opacity: 0.2, transparent: true})
                const plane = new THREE.Mesh( geometry, material )
                plane.lookAt(new THREE.Vector3(...item.norm))
                this.scene.add( plane )
            } else if (item.figure == "line") {
            } else if (item.figure == "point") {
            } else if (item.figure == "empty") {
            } else if (item.figure == "space") {
                
            }
        }
    
        // let geometry = new THREE.BoxGeometry( 0.2, 0.2, 0.2 );
        // let material = new THREE.MeshNormalMaterial();
    
        // this.mesh = new THREE.Mesh( geometry, material );
        // this.scene.add( this.mesh );
    
        this.renderer = new THREE.WebGLRenderer( { antialias: true, alpha: true } );
        this.renderer.setSize(640, 640)
        // this.renderer.setSize( window.innerWidth, window.innerHeight );
        this.renderer.setClearColor( 0xffffff, 0 )
        this.$refs.canvas.appendChild( this.renderer.domElement );
    
        this.animate()
    },
    methods: {
        animate() {
            requestAnimationFrame( this.animate );
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
    border: solid 2px black;
    border-radius: 10px;
}
</style>
