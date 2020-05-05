<template>
    <div class="demo">
        <h1>Hello there!</h1>
        <div class="language- line-numbers-mode" ref="demo">
            <pre class="language-text"><code class="editor-container"><textarea class="editor" v-model="codeValue"/></code></pre>
            <div class="line-numbers-wrapper">
                <template v-for="k in lineNumbers" v-key="k">
                    <span class="line-number">{{k}}</span>
                    <br>
                </template>
            </div>
        </div>
        <Button>Run</Button>
        <!-- <button class="btn run">Run</button> -->
    </div>
</template>

<script>
export default {
    name: 'demo',
    props: {
        code: {
            required: true,
            type: String
        }
    },
    data() {
        return {
            codeValue: this.code
        }
    },
    computed: {
        lineNumbers() {
            return this.codeValue.split('\n').length
        },
        editorHeight() {
            return this.lineNumbers * 1.0 + 2.0
        }
    },
    watch: {
        editorHeight(val) {
            this.$refs.demo.style.height = val
        },
        codeProp(val) {
            this.code = val
        }
    }
}
</script>

<style scoped>
.demo {
    display: flex;
    flex-direction: column;
    align-content: flex-start;
    justify-content: center;
}
.editor {
    background-color: #282c34;
    color: #fff;
    border: none;
    height: auto;
    outline-width: 0;
    resize: none;
    margin: 0;
    padding: 0;
    line-height: 1.440rem;
    height: 600px;
    overflow-x: scroll;
    width: 100%;
    white-space: nowrap;
}
.editor-container {
}
.language-text {
    margin-top: 0 !important;
}
.langauge- {
}
.line-numbers-wrapper {
    margin-top: -2px !important;
}
</style>