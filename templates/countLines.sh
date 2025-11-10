#Set template to any possible template for getting number of lines
#template=
# sed -e '/\/\/.*/d' -e '/^\s*$/d' -E -e '/^\(/d' ${template} | wc -l
