<template>
    <div class="demo">
        <h1>Hello there!</h1>
        <div class="language- line-numbers-mode" ref="demo">
            <pre class="language-text"><code class="editor-container"><textarea ref="editor" class="editor" v-model="codeValue"/></code></pre>
            <div class="line-numbers-wrapper">
                <template v-for="k in lineNumbers" v-key="k">
                    <span class="line-number">{{k}}</span>
                    <br>
                </template>
            </div>
        </div>
        <Button>Run</Button>
        <!-- <button class="btn run">Run</button> -->

        <div class="custom-block danger">
            <p class="custom-block-title">Error</p>
            <p>{{ error }}</p>
        </div>

        <div class="custom-block tip">
            <p class="custom-block-title">Output</p>
            <p>{{ output }}</p>
        </div>
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
            codeValue: this.code,
            error: 'Not an error',
            output: 'Am I an output?'
        }
    },
    created() {
        setTimeout(() => {
            this.$refs.editor.style.height = this.lineNumbers * 23.0 + 10.0 + 'px'
        }, 0)
    },
    computed: {
        lineNumbers() {
            return this.codeValue.split('\n').length
        },
        editorHeight() {
            return this.lineNumbers * 23.0 + 10.0
        }
    },
    watch: {
        editorHeight(val) {
            this.$refs.editor.style.height = val + 'px'
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
    outline-width: 0;
    resize: none;
    margin: 0;
    padding: 0;
    line-height: 1.440rem;
    overflow-x: scroll;
    width: 100%;
    white-space: nowrap;
    overflow-y: hidden;
}
.editor-container {
}
.language-text {
    margin-top: 0 !important;
    margin-bottom: 0 !important;
}
.langauge- {
}
.line-numbers-wrapper {
    margin-top: -2px !important;
}
::-webkit-scrollbar {
  width: 10px;
}
::-webkit-scrollbar-track {
  background: #282c34;
}
::-webkit-scrollbar-thumb {
  background: #555;
}
::-webkit-scrollbar-thumb:hover {
  background: #444;
}
</style>