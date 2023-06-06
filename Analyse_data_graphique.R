#Package pour importer les fichiers et pour faire des graphiques
library(readr)
library(ggplot2)

#Importation du fichier
df <- read_delim("Valence_bis.csv", 
                        delim = ";", escape_double = FALSE, trim_ws = TRUE)


#Pour des graphiques avec la moyenne des scores d'une variable selon les odeurs
ggplot(df) +
  aes(x = Odeurs, y = Moyenne, fill = Odeurs) +
  geom_col() +
  geom_errorbar(aes(ymin = Moyenne - Ecart_type, ymax = Moyenne + Ecart_type), width = 0.2)+
  scale_fill_hue(direction = 1) +
  labs(
    x = "Odeurs",
    y = "Angle moyen (en degrés)",
    fill = "Odeurs"
  ) +
  coord_cartesian(ylim = c(50, 100)) +
  theme_minimal() +
  theme(
    plot.title = element_text(face = "bold",
                              hjust = 0.5),
    axis.title.y = element_text(size = 12L,
                                face = "bold"),
    axis.title.x = element_text(size = 12L,
                                face = "bold")
  ) 

#Pour un graphique des scores de chaque participant selon les différentes conditions
ggplot(df) +
  aes(x = Odeurs, y = `Moyenne`, fill = Odeurs) +
  geom_col() +
  scale_fill_hue(direction = 1) +
  labs(
    x = "Participants",
    y = "Score moyen de valence",
    fill = "Odeurs"
  ) +
  coord_cartesian(ylim = c(0, 9)) +
  theme_minimal() +
  theme(
    axis.title.y = element_text(size = 13L,
                                face = "bold"),
    axis.title.x = element_text(size = 13L,
                                face = "bold")
  ) +
  facet_wrap(vars(Participants), ncol = 4L, nrow = 8L)
  
  