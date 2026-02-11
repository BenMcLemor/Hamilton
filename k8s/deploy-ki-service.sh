#!/bin/bash
# Hamilton KI-Service auf K3d deployen
# LOKAL auf WSL!

set -e

echo "=== Hamilton KI-Service Deployment ==="

# 1. Namespace anlegen
kubectl create namespace hamilton-ai --dry-run=client -o yaml | kubectl apply -f -

# 2. Deployment und Service anwenden
cat << 'EOF' | kubectl apply -f -
---
apiVersion: apps/v1
kind: Deployment
metadata:
  name: ai-classifier
  namespace: hamilton-ai
spec:
  replicas: 1
  selector:
    matchLabels:
      app: ai-classifier
  template:
    metadata:
      labels:
        app: ai-classifier
    spec:
      containers:
      - name: classifier
        image: benmclemor/hamilton-ai-classifier:latest
        imagePullPolicy: IfNotPresent
        ports:
        - containerPort: 8000
        env:
        - name: ENVIRONMENT
          value: "simulation"
---
apiVersion: v1
kind: Service
metadata:
  name: ai-classifier
  namespace: hamilton-ai
spec:
  selector:
    app: ai-classifier
  ports:
  - port: 80
    targetPort: 8000
  type: LoadBalancer
EOF

# 3. Pod-Status prüfen
echo "Warte auf Pods..."
kubectl wait --namespace hamilton-ai \
  --for=condition=ready pod \
  --selector=app=ai-classifier \
  --timeout=60s || true

# 4. Zugang zeigen
echo ""
echo "✅ KI-Service deployed!"
echo ""
echo "Teste den Service:"
echo "  kubectl port-forward -n hamilton-ai svc/ai-classifier 8000:80"
echo ""
echo "Dann: curl http://localhost:8000"
