function loadTags(handleTagsLoaded)
{
    var counter = 0;
    var incCouter = ()=>{
        counter++;
        if(counter == LOADER_API_tagsToLoad.length) {
            if(typeof handleTagsLoaded != "undefined") handleTagsLoaded();
        }
    }
    
    LOADER_API_tagsToLoad.forEach((tagsObj)=>{
        loadNthTag(0, tagsObj.tags, tagsObj.whereToAppend, tagsObj.waitLoadOrError, ()=>{
            if(typeof tagsObj.onFinish != "undefined") tagsObj.onFinish();
            incCouter();
        });
    });
}
function loadNthTag(tagNum, tags, whereToAppend, waitLoadOrError, handleTagsLoaded)
{
    var tagProps = tags[tagNum].props;
    var tagType = tags[tagNum].tagType;
    var content = tags[tagNum].content;
    loadTag(tagType, tagProps, content, whereToAppend, waitLoadOrError, ()=>{
        if(tagNum+1 < tags.length) loadNthTag(tagNum+1, tags, whereToAppend, waitLoadOrError, handleTagsLoaded);
        else if(typeof handleTagsLoaded != "undefined") handleTagsLoaded();
    });
}

function loadTag(tagType, tagProps, content, whereToAppend, waitLoadOrError, handleTagLoaded)
{
    if(typeof tagProps == "undefined") tagProps = {};
    
    var tag = document.createElement(tagType);

    Object.getOwnPropertyNames(tagProps).forEach((propName)=>{
        tag.setAttribute(propName, tagProps[propName]);
    });

    
    if(typeof content != "undefined") tag.innerHTML = content;

    var onComplete = (event)=>{
        if(typeof handleTagLoaded != "undefined") handleTagLoaded();
    }

    if(typeof waitLoadOrError == "undefined") waitLoadOrError = true;
    if(waitLoadOrError)
    {
        tag.addEventListener('load', onComplete);
        tag.addEventListener('error', onComplete);
    }
    else onComplete();

    whereToAppend.appendChild(tag);
}

loadTags(LOADER_API_contentLoaded);