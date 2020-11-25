const exBar=document.querySelector('.exBar');
const displayedImg=document.querySelector('.displayedImg');
for(let i=2;i<=5;i++)
{
    const newImg=document.createElement('img');
    newImg.setAttribute('src',i+'.jpg');
    exBar.appendChild(newImg);
    newImg.onclick=function(e){
        displayedImg.src=e.target.src;
    }
}
const btn=document.querySelector('button');
const overlay=document.querySelector('.overlay');

function darken()
{
    const btnClass=btn.getAttribute('class');
   if(btnClass==='dark'){
        overlay.style.backgroundColor='rgba(0,0,0,0.5)';
        btn.textContent='light';
        btn.setAttribute('class','light');
   }else{
        overlay.style.backgroundColor='rgba(0,0,0,0)';
        btn.textContent='dark';
        btn.setAttribute('class','dark');
   }
}
btn.addEventListener('click',darken);