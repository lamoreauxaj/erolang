<template>
    <button class="btn" v-bind="$attrs">
        <slot></slot>
    </button>
</template>

<script>
export default {
    name: 'button'
}
</script>

<style scoped>
.btn {
    margin-left: auto;
    margin-top: 10px;
    margin-right: 20px;
    padding: 3px 0;
    width: 60px;
    justify-self: end;
    background-color: #282c34;
    color: #fff;
    border: none;
    border-bottom: 2px solid rgba(0, 0, 0, 255);
    font-size: 0.9rem;
    font-weight: 500;
    line-height: 1.4rem;
    border-radius: 5px;
    box-shadow: 0 2px 2px 0 rgba(0,0,0,0.14), 0 3px 1px -2px rgba(0,0,0,0.12), 0 1px 5px 0 rgba(0,0,0,0.2);
    cursor: pointer;
    font-family: -apple-system, BlinkMacSystemFont, "Segoe UI", Roboto, Oxygen, Ubuntu, Cantarell, "Fira Sans", "Droid Sans", "Helvetica Neue", sans-serif;
    outline-width: 0;
}
.btn:hover {
    color: #acacac;
    border-bottom: 2px solid #46bd87;
}
</style>