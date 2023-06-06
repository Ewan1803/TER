library(readr)#package pour ouvrir les fichiers .csv


#pour importer le fichier .csv avec les données de puissance
df <- read_delim("M1/TER/Data_velo/mar_tec.csv", 
                          delim = ";", escape_double = FALSE, trim_ws = TRUE)

summary(df)

df <- df[df$StartTime == df$"ns1:Id", ]#pour sélectionner uniquement les lignes correspondant au premier circuit, c'est-à-dire le parcours des 5 km

df <- df[df$"ns2:Watts" >= 20 & df$"ns2:Watts" <= 400,]#pour enlever les valeurs aberrantes, (on conserve ce qui est entre 20 et 400 Watts)

mean(df$"ns2:Watts") #pour avoir la puissance moyenne
     
