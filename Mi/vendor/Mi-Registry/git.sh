COMMIT_MESSAGE=$1

git add .

echo $COMMIT_MESSAGE
git commit -m "$COMMIT_MESSAGE"
git push -u origin main